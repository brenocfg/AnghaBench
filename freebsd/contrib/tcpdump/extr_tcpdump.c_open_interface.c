#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sysctl ;
typedef  int /*<<< orphan*/  pcap_t ;
typedef  int /*<<< orphan*/  parent ;
typedef  int /*<<< orphan*/  newdev ;
struct TYPE_3__ {int /*<<< orphan*/  ndo_snaplen; int /*<<< orphan*/  ndo_tstamp_precision; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ Bflag ; 
 scalar_t__ Iflag ; 
 scalar_t__ Jflag ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_NO_SUCH_DEVICE ; 
 int PCAP_ERROR_PERM_DENIED ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 int PCAP_WARNING ; 
 int PCAP_WARNING_PROMISC_NOTSUP ; 
 int Qflag ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  error (char*,char const*,...) ; 
 scalar_t__ immediate_mode ; 
 int jflag ; 
 int pcap_activate (int /*<<< orphan*/ *) ; 
 int pcap_can_set_rfmon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcap_create (char const*,char*) ; 
 char* pcap_geterr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pcap_open_live (char const*,int /*<<< orphan*/ ,int,int,char*) ; 
 int pcap_set_buffer_size (int /*<<< orphan*/ *,scalar_t__) ; 
 int pcap_set_immediate_mode (int /*<<< orphan*/ *,int) ; 
 int pcap_set_promisc (int /*<<< orphan*/ *,int) ; 
 int pcap_set_rfmon (int /*<<< orphan*/ *,int) ; 
 int pcap_set_snaplen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pcap_set_timeout (int /*<<< orphan*/ *,int) ; 
 int pcap_set_tstamp_precision (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pcap_set_tstamp_type (int /*<<< orphan*/ *,int) ; 
 int pcap_setdirection (int /*<<< orphan*/ *,int) ; 
 char* pcap_statustostr (int) ; 
 int /*<<< orphan*/  pflag ; 
 int /*<<< orphan*/  show_tstamp_types_and_exit (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int supports_monitor_mode ; 
 int /*<<< orphan*/  sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* tstamp_precision_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,char const*,...) ; 

__attribute__((used)) static pcap_t *
open_interface(const char *device, netdissect_options *ndo, char *ebuf)
{
	pcap_t *pc;
#ifdef HAVE_PCAP_CREATE
	int status;
	char *cp;
#endif

#ifdef HAVE_PCAP_CREATE
	pc = pcap_create(device, ebuf);
	if (pc == NULL) {
		/*
		 * If this failed with "No such device", that means
		 * the interface doesn't exist; return NULL, so that
		 * the caller can see whether the device name is
		 * actually an interface index.
		 */
		if (strstr(ebuf, "No such device") != NULL)
			return (NULL);
		error("%s", ebuf);
	}
#ifdef HAVE_PCAP_SET_TSTAMP_TYPE
	if (Jflag)
		show_tstamp_types_and_exit(pc, device);
#endif
#ifdef HAVE_PCAP_SET_TSTAMP_PRECISION
	status = pcap_set_tstamp_precision(pc, ndo->ndo_tstamp_precision);
	if (status != 0)
		error("%s: Can't set %ssecond time stamp precision: %s",
			device,
			tstamp_precision_to_string(ndo->ndo_tstamp_precision),
			pcap_statustostr(status));
#endif

#ifdef HAVE_PCAP_SET_IMMEDIATE_MODE
	if (immediate_mode) {
		status = pcap_set_immediate_mode(pc, 1);
		if (status != 0)
			error("%s: Can't set immediate mode: %s",
			device,
			pcap_statustostr(status));
	}
#endif
	/*
	 * Is this an interface that supports monitor mode?
	 */
	if (pcap_can_set_rfmon(pc) == 1)
		supports_monitor_mode = 1;
	else
		supports_monitor_mode = 0;
	status = pcap_set_snaplen(pc, ndo->ndo_snaplen);
	if (status != 0)
		error("%s: Can't set snapshot length: %s",
		    device, pcap_statustostr(status));
	status = pcap_set_promisc(pc, !pflag);
	if (status != 0)
		error("%s: Can't set promiscuous mode: %s",
		    device, pcap_statustostr(status));
	if (Iflag) {
		status = pcap_set_rfmon(pc, 1);
		if (status != 0)
			error("%s: Can't set monitor mode: %s",
			    device, pcap_statustostr(status));
	}
	status = pcap_set_timeout(pc, 1000);
	if (status != 0)
		error("%s: pcap_set_timeout failed: %s",
		    device, pcap_statustostr(status));
	if (Bflag != 0) {
		status = pcap_set_buffer_size(pc, Bflag);
		if (status != 0)
			error("%s: Can't set buffer size: %s",
			    device, pcap_statustostr(status));
	}
#ifdef HAVE_PCAP_SET_TSTAMP_TYPE
	if (jflag != -1) {
		status = pcap_set_tstamp_type(pc, jflag);
		if (status < 0)
			error("%s: Can't set time stamp type: %s",
		              device, pcap_statustostr(status));
	}
#endif
	status = pcap_activate(pc);
	if (status < 0) {
		/*
		 * pcap_activate() failed.
		 */
		cp = pcap_geterr(pc);
		if (status == PCAP_ERROR)
			error("%s", cp);
		else if (status == PCAP_ERROR_NO_SUCH_DEVICE) {
			/*
			 * Return an error for our caller to handle.
			 */
			snprintf(ebuf, PCAP_ERRBUF_SIZE, "%s: %s\n(%s)",
			    device, pcap_statustostr(status), cp);
			pcap_close(pc);
			return (NULL);
		} else if (status == PCAP_ERROR_PERM_DENIED && *cp != '\0')
			error("%s: %s\n(%s)", device,
			    pcap_statustostr(status), cp);
#ifdef __FreeBSD__
		else if (status == PCAP_ERROR_RFMON_NOTSUP &&
		    strncmp(device, "wlan", 4) == 0) {
			char parent[8], newdev[8];
			char sysctl[32];
			size_t s = sizeof(parent);

			snprintf(sysctl, sizeof(sysctl),
			    "net.wlan.%d.%%parent", atoi(device + 4));
			sysctlbyname(sysctl, parent, &s, NULL, 0);
			strlcpy(newdev, device, sizeof(newdev));
			/* Suggest a new wlan device. */
			/* FIXME: incrementing the index this way is not going to work well
			 * when the index is 9 or greater but the only consequence in this
			 * specific case would be an error message that looks a bit odd.
			 */
			newdev[strlen(newdev)-1]++;
			error("%s is not a monitor mode VAP\n"
			    "To create a new monitor mode VAP use:\n"
			    "  ifconfig %s create wlandev %s wlanmode monitor\n"
			    "and use %s as the tcpdump interface",
			    device, newdev, parent, newdev);
		}
#endif
		else
			error("%s: %s", device,
			    pcap_statustostr(status));
	} else if (status > 0) {
		/*
		 * pcap_activate() succeeded, but it's warning us
		 * of a problem it had.
		 */
		cp = pcap_geterr(pc);
		if (status == PCAP_WARNING)
			warning("%s", cp);
		else if (status == PCAP_WARNING_PROMISC_NOTSUP &&
		         *cp != '\0')
			warning("%s: %s\n(%s)", device,
			    pcap_statustostr(status), cp);
		else
			warning("%s: %s", device,
			    pcap_statustostr(status));
	}
#ifdef HAVE_PCAP_SETDIRECTION
	if (Qflag != -1) {
		status = pcap_setdirection(pc, Qflag);
		if (status != 0)
			error("%s: pcap_setdirection() failed: %s",
			      device,  pcap_geterr(pc));
		}
#endif /* HAVE_PCAP_SETDIRECTION */
#else /* HAVE_PCAP_CREATE */
	*ebuf = '\0';
	pc = pcap_open_live(device, ndo->ndo_snaplen, !pflag, 1000, ebuf);
	if (pc == NULL) {
		/*
		 * If this failed with "No such device", that means
		 * the interface doesn't exist; return NULL, so that
		 * the caller can see whether the device name is
		 * actually an interface index.
		 */
		if (strstr(ebuf, "No such device") != NULL)
			return (NULL);
		error("%s", ebuf);
	}
	if (*ebuf)
		warning("%s", ebuf);
#endif /* HAVE_PCAP_CREATE */

	return (pc);
}