#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pcap_bpf {int must_do_on_close; int /*<<< orphan*/ * device; int /*<<< orphan*/  zbufsize; int /*<<< orphan*/ * zbuf2; int /*<<< orphan*/ * zbuf1; scalar_t__ zerocopy; } ;
struct ifreq {int ifm_current; int ifr_media; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  ifm_name; } ;
struct ifmediareq {int ifm_current; int ifr_media; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  ifm_name; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_5__ {int /*<<< orphan*/ * buffer; struct pcap_bpf* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_LOCAL ; 
 int IFM_IEEE80211_MONITOR ; 
 int /*<<< orphan*/ * MAP_FAILED ; 
 int MUST_CLEAR_RFMON ; 
 int MUST_DESTROY_USBUS ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  SIOCIFDESTROY ; 
 int /*<<< orphan*/  SIOCSIFMEDIA ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ if_nametoindex (int /*<<< orphan*/ *) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_1__*) ; 
 int /*<<< orphan*/  pcap_remove_from_pcaps_to_close (TYPE_1__*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
pcap_cleanup_bpf(pcap_t *p)
{
	struct pcap_bpf *pb = p->priv;
#ifdef HAVE_BSD_IEEE80211
	int sock;
	struct ifmediareq req;
	struct ifreq ifr;
#endif

	if (pb->must_do_on_close != 0) {
		/*
		 * There's something we have to do when closing this
		 * pcap_t.
		 */
#ifdef HAVE_BSD_IEEE80211
		if (pb->must_do_on_close & MUST_CLEAR_RFMON) {
			/*
			 * We put the interface into rfmon mode;
			 * take it out of rfmon mode.
			 *
			 * XXX - if somebody else wants it in rfmon
			 * mode, this code cannot know that, so it'll take
			 * it out of rfmon mode.
			 */
			sock = socket(AF_INET, SOCK_DGRAM, 0);
			if (sock == -1) {
				fprintf(stderr,
				    "Can't restore interface flags (socket() failed: %s).\n"
				    "Please adjust manually.\n",
				    strerror(errno));
			} else {
				memset(&req, 0, sizeof(req));
				strncpy(req.ifm_name, pb->device,
				    sizeof(req.ifm_name));
				if (ioctl(sock, SIOCGIFMEDIA, &req) < 0) {
					fprintf(stderr,
					    "Can't restore interface flags (SIOCGIFMEDIA failed: %s).\n"
					    "Please adjust manually.\n",
					    strerror(errno));
				} else {
					if (req.ifm_current & IFM_IEEE80211_MONITOR) {
						/*
						 * Rfmon mode is currently on;
						 * turn it off.
						 */
						memset(&ifr, 0, sizeof(ifr));
						(void)strncpy(ifr.ifr_name,
						    pb->device,
						    sizeof(ifr.ifr_name));
						ifr.ifr_media =
						    req.ifm_current & ~IFM_IEEE80211_MONITOR;
						if (ioctl(sock, SIOCSIFMEDIA,
						    &ifr) == -1) {
							fprintf(stderr,
							    "Can't restore interface flags (SIOCSIFMEDIA failed: %s).\n"
							    "Please adjust manually.\n",
							    strerror(errno));
						}
					}
				}
				close(sock);
			}
		}
#endif /* HAVE_BSD_IEEE80211 */

#if defined(__FreeBSD__) && defined(SIOCIFCREATE2)
		/*
		 * Attempt to destroy the usbusN interface that we created.
		 */
		if (pb->must_do_on_close & MUST_DESTROY_USBUS) {
			if (if_nametoindex(pb->device) > 0) {
				int s;

				s = socket(AF_LOCAL, SOCK_DGRAM, 0);
				if (s >= 0) {
					strlcpy(ifr.ifr_name, pb->device,
					    sizeof(ifr.ifr_name));
					ioctl(s, SIOCIFDESTROY, &ifr);
					close(s);
				}
			}
		}
#endif /* defined(__FreeBSD__) && defined(SIOCIFCREATE2) */
		/*
		 * Take this pcap out of the list of pcaps for which we
		 * have to take the interface out of some mode.
		 */
		pcap_remove_from_pcaps_to_close(p);
		pb->must_do_on_close = 0;
	}

#ifdef HAVE_ZEROCOPY_BPF
	if (pb->zerocopy) {
		/*
		 * Delete the mappings.  Note that p->buffer gets
		 * initialized to one of the mmapped regions in
		 * this case, so do not try and free it directly;
		 * null it out so that pcap_cleanup_live_common()
		 * doesn't try to free it.
		 */
		if (pb->zbuf1 != MAP_FAILED && pb->zbuf1 != NULL)
			(void) munmap(pb->zbuf1, pb->zbufsize);
		if (pb->zbuf2 != MAP_FAILED && pb->zbuf2 != NULL)
			(void) munmap(pb->zbuf2, pb->zbufsize);
		p->buffer = NULL;
	}
#endif
	if (pb->device != NULL) {
		free(pb->device);
		pb->device = NULL;
	}
	pcap_cleanup_live_common(p);
}