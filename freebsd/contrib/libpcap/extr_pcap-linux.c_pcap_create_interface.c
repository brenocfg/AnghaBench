#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct pcap_linux {int dummy; } ;
struct TYPE_6__ {int tstamp_precision_count; int /*<<< orphan*/ * tstamp_precision_list; int /*<<< orphan*/  can_set_rfmon_op; int /*<<< orphan*/  activate_op; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PCAP_TSTAMP_PRECISION_MICRO ; 
 int /*<<< orphan*/  PCAP_TSTAMP_PRECISION_NANO ; 
 int /*<<< orphan*/  errno ; 
 int iface_ethtool_get_ts_info (char const*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  pcap_activate_linux ; 
 int /*<<< orphan*/  pcap_can_set_rfmon_linux ; 
 int /*<<< orphan*/  pcap_close (TYPE_1__*) ; 
 TYPE_1__* pcap_create_common (char*,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

pcap_t *
pcap_create_interface(const char *device, char *ebuf)
{
	pcap_t *handle;

	handle = pcap_create_common(ebuf, sizeof (struct pcap_linux));
	if (handle == NULL)
		return NULL;

	handle->activate_op = pcap_activate_linux;
	handle->can_set_rfmon_op = pcap_can_set_rfmon_linux;

#if defined(HAVE_LINUX_NET_TSTAMP_H) && defined(PACKET_TIMESTAMP)
	/*
	 * See what time stamp types we support.
	 */
	if (iface_ethtool_get_ts_info(device, handle, ebuf) == -1) {
		pcap_close(handle);
		return NULL;
	}
#endif

#if defined(SIOCGSTAMPNS) && defined(SO_TIMESTAMPNS)
	/*
	 * We claim that we support microsecond and nanosecond time
	 * stamps.
	 *
	 * XXX - with adapter-supplied time stamps, can we choose
	 * microsecond or nanosecond time stamps on arbitrary
	 * adapters?
	 */
	handle->tstamp_precision_count = 2;
	handle->tstamp_precision_list = malloc(2 * sizeof(u_int));
	if (handle->tstamp_precision_list == NULL) {
		pcap_fmt_errmsg_for_errno(ebuf, PCAP_ERRBUF_SIZE,
		    errno, "malloc");
		pcap_close(handle);
		return NULL;
	}
	handle->tstamp_precision_list[0] = PCAP_TSTAMP_PRECISION_MICRO;
	handle->tstamp_precision_list[1] = PCAP_TSTAMP_PRECISION_NANO;
#endif /* defined(SIOCGSTAMPNS) && defined(SO_TIMESTAMPNS) */

	return handle;
}