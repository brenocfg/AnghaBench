#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  PCAP_ERROR 142 
#define  PCAP_ERROR_ACTIVATED 141 
#define  PCAP_ERROR_BREAK 140 
#define  PCAP_ERROR_CANTSET_TSTAMP_TYPE 139 
#define  PCAP_ERROR_IFACE_NOT_UP 138 
#define  PCAP_ERROR_NOT_ACTIVATED 137 
#define  PCAP_ERROR_NOT_RFMON 136 
#define  PCAP_ERROR_NO_SUCH_DEVICE 135 
#define  PCAP_ERROR_PERM_DENIED 134 
#define  PCAP_ERROR_PROMISC_PERM_DENIED 133 
#define  PCAP_ERROR_RFMON_NOTSUP 132 
#define  PCAP_ERROR_TSTAMP_PRECISION_NOTSUP 131 
#define  PCAP_WARNING 130 
#define  PCAP_WARNING_PROMISC_NOTSUP 129 
#define  PCAP_WARNING_TSTAMP_TYPE_NOTSUP 128 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,int) ; 

const char *
pcap_statustostr(int errnum)
{
	static char ebuf[15+10+1];

	switch (errnum) {

	case PCAP_WARNING:
		return("Generic warning");

	case PCAP_WARNING_TSTAMP_TYPE_NOTSUP:
		return ("That type of time stamp is not supported by that device");

	case PCAP_WARNING_PROMISC_NOTSUP:
		return ("That device doesn't support promiscuous mode");

	case PCAP_ERROR:
		return("Generic error");

	case PCAP_ERROR_BREAK:
		return("Loop terminated by pcap_breakloop");

	case PCAP_ERROR_NOT_ACTIVATED:
		return("The pcap_t has not been activated");

	case PCAP_ERROR_ACTIVATED:
		return ("The setting can't be changed after the pcap_t is activated");

	case PCAP_ERROR_NO_SUCH_DEVICE:
		return ("No such device exists");

	case PCAP_ERROR_RFMON_NOTSUP:
		return ("That device doesn't support monitor mode");

	case PCAP_ERROR_NOT_RFMON:
		return ("That operation is supported only in monitor mode");

	case PCAP_ERROR_PERM_DENIED:
		return ("You don't have permission to capture on that device");

	case PCAP_ERROR_IFACE_NOT_UP:
		return ("That device is not up");

	case PCAP_ERROR_CANTSET_TSTAMP_TYPE:
		return ("That device doesn't support setting the time stamp type");

	case PCAP_ERROR_PROMISC_PERM_DENIED:
		return ("You don't have permission to capture in promiscuous mode on that device");

	case PCAP_ERROR_TSTAMP_PRECISION_NOTSUP:
		return ("That device doesn't support that time stamp precision");
	}
	(void)pcap_snprintf(ebuf, sizeof ebuf, "Unknown error: %d", errnum);
	return(ebuf);
}