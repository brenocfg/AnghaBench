#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pcap_linux {int must_do_on_close; char* device; char* mondevice; int /*<<< orphan*/  oldmode; } ;
struct nl80211_state {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  mode; } ;
struct TYPE_9__ {int /*<<< orphan*/  ifrn_name; } ;
struct iwreq {int ifr_flags; TYPE_2__ u; TYPE_1__ ifr_ifrn; int /*<<< orphan*/  ifr_name; } ;
struct ifreq {int ifr_flags; TYPE_2__ u; TYPE_1__ ifr_ifrn; int /*<<< orphan*/  ifr_name; } ;
struct TYPE_11__ {char* errbuf; int /*<<< orphan*/  fd; struct pcap_linux* priv; } ;
typedef  TYPE_3__ pcap_t ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int MUST_CLEAR_PROMISC ; 
 int MUST_CLEAR_RFMON ; 
 int MUST_DELETE_MONIF ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIWMODE ; 
 int del_mon_if (TYPE_3__*,int /*<<< orphan*/ ,struct nl80211_state*,char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwreq*) ; 
 int /*<<< orphan*/  memset (struct iwreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl80211_cleanup (struct nl80211_state*) ; 
 int nl80211_init (TYPE_3__*,struct nl80211_state*,char*) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_3__*) ; 
 int /*<<< orphan*/  pcap_remove_from_pcaps_to_close (TYPE_3__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void	pcap_cleanup_linux( pcap_t *handle )
{
	struct pcap_linux *handlep = handle->priv;
	struct ifreq	ifr;
#ifdef HAVE_LIBNL
	struct nl80211_state nlstate;
	int ret;
#endif /* HAVE_LIBNL */
#ifdef IW_MODE_MONITOR
	int oldflags;
	struct iwreq ireq;
#endif /* IW_MODE_MONITOR */

	if (handlep->must_do_on_close != 0) {
		/*
		 * There's something we have to do when closing this
		 * pcap_t.
		 */
		if (handlep->must_do_on_close & MUST_CLEAR_PROMISC) {
			/*
			 * We put the interface into promiscuous mode;
			 * take it out of promiscuous mode.
			 *
			 * XXX - if somebody else wants it in promiscuous
			 * mode, this code cannot know that, so it'll take
			 * it out of promiscuous mode.  That's not fixable
			 * in 2.0[.x] kernels.
			 */
			memset(&ifr, 0, sizeof(ifr));
			strlcpy(ifr.ifr_name, handlep->device,
			    sizeof(ifr.ifr_name));
			if (ioctl(handle->fd, SIOCGIFFLAGS, &ifr) == -1) {
				fprintf(stderr,
				    "Can't restore interface %s flags (SIOCGIFFLAGS failed: %s).\n"
				    "Please adjust manually.\n"
				    "Hint: This can't happen with Linux >= 2.2.0.\n",
				    handlep->device, strerror(errno));
			} else {
				if (ifr.ifr_flags & IFF_PROMISC) {
					/*
					 * Promiscuous mode is currently on;
					 * turn it off.
					 */
					ifr.ifr_flags &= ~IFF_PROMISC;
					if (ioctl(handle->fd, SIOCSIFFLAGS,
					    &ifr) == -1) {
						fprintf(stderr,
						    "Can't restore interface %s flags (SIOCSIFFLAGS failed: %s).\n"
						    "Please adjust manually.\n"
						    "Hint: This can't happen with Linux >= 2.2.0.\n",
						    handlep->device,
						    strerror(errno));
					}
				}
			}
		}

#ifdef HAVE_LIBNL
		if (handlep->must_do_on_close & MUST_DELETE_MONIF) {
			ret = nl80211_init(handle, &nlstate, handlep->device);
			if (ret >= 0) {
				ret = del_mon_if(handle, handle->fd, &nlstate,
				    handlep->device, handlep->mondevice);
				nl80211_cleanup(&nlstate);
			}
			if (ret < 0) {
				fprintf(stderr,
				    "Can't delete monitor interface %s (%s).\n"
				    "Please delete manually.\n",
				    handlep->mondevice, handle->errbuf);
			}
		}
#endif /* HAVE_LIBNL */

#ifdef IW_MODE_MONITOR
		if (handlep->must_do_on_close & MUST_CLEAR_RFMON) {
			/*
			 * We put the interface into rfmon mode;
			 * take it out of rfmon mode.
			 *
			 * XXX - if somebody else wants it in rfmon
			 * mode, this code cannot know that, so it'll take
			 * it out of rfmon mode.
			 */

			/*
			 * First, take the interface down if it's up;
			 * otherwise, we might get EBUSY.
			 * If we get errors, just drive on and print
			 * a warning if we can't restore the mode.
			 */
			oldflags = 0;
			memset(&ifr, 0, sizeof(ifr));
			strlcpy(ifr.ifr_name, handlep->device,
			    sizeof(ifr.ifr_name));
			if (ioctl(handle->fd, SIOCGIFFLAGS, &ifr) != -1) {
				if (ifr.ifr_flags & IFF_UP) {
					oldflags = ifr.ifr_flags;
					ifr.ifr_flags &= ~IFF_UP;
					if (ioctl(handle->fd, SIOCSIFFLAGS, &ifr) == -1)
						oldflags = 0;	/* didn't set, don't restore */
				}
			}

			/*
			 * Now restore the mode.
			 */
			strlcpy(ireq.ifr_ifrn.ifrn_name, handlep->device,
			    sizeof ireq.ifr_ifrn.ifrn_name);
			ireq.u.mode = handlep->oldmode;
			if (ioctl(handle->fd, SIOCSIWMODE, &ireq) == -1) {
				/*
				 * Scientist, you've failed.
				 */
				fprintf(stderr,
				    "Can't restore interface %s wireless mode (SIOCSIWMODE failed: %s).\n"
				    "Please adjust manually.\n",
				    handlep->device, strerror(errno));
			}

			/*
			 * Now bring the interface back up if we brought
			 * it down.
			 */
			if (oldflags != 0) {
				ifr.ifr_flags = oldflags;
				if (ioctl(handle->fd, SIOCSIFFLAGS, &ifr) == -1) {
					fprintf(stderr,
					    "Can't bring interface %s back up (SIOCSIFFLAGS failed: %s).\n"
					    "Please adjust manually.\n",
					    handlep->device, strerror(errno));
				}
			}
		}
#endif /* IW_MODE_MONITOR */

		/*
		 * Take this pcap out of the list of pcaps for which we
		 * have to take the interface out of some mode.
		 */
		pcap_remove_from_pcaps_to_close(handle);
	}

	if (handlep->mondevice != NULL) {
		free(handlep->mondevice);
		handlep->mondevice = NULL;
	}
	if (handlep->device != NULL) {
		free(handlep->device);
		handlep->device = NULL;
	}
	pcap_cleanup_live_common(handle);
}