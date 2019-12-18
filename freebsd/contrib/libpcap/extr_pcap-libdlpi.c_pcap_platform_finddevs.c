#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pcap_if_list_t ;
struct TYPE_5__ {scalar_t__ lw_err; TYPE_2__* lw_list; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ linkwalk_t ;
struct TYPE_6__ {struct TYPE_6__* lnl_next; int /*<<< orphan*/  linkname; } ;
typedef  TYPE_2__ linknamelist_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  dlpi_walk (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/ * find_or_add_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  get_if_flags ; 
 int /*<<< orphan*/  is_dlpi_interface ; 
 int /*<<< orphan*/  list_interfaces ; 
 int pcap_findalldevs_interfaces (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (char*,int /*<<< orphan*/ ,scalar_t__,char*) ; 

int
pcap_platform_finddevs(pcap_if_list_t *devlistp, char *errbuf)
{
	int retv = 0;

	linknamelist_t	*entry, *next;
	linkwalk_t	lw = {NULL, 0};
	int 		save_errno;

	/*
	 * Get the list of regular interfaces first.
	 */
	if (pcap_findalldevs_interfaces(devlistp, errbuf,
	    is_dlpi_interface, get_if_flags) == -1)
		return (-1);	/* failure */

	/* dlpi_walk() for loopback will be added here. */

	/*
	 * Find all DLPI devices in the current zone.
	 *
	 * XXX - will pcap_findalldevs_interfaces() find any devices
	 * outside the current zone?  If not, the only reason to call
	 * it would be to get the interface addresses.
	 */
	dlpi_walk(list_interfaces, &lw, 0);

	if (lw.lw_err != 0) {
		pcap_fmt_errmsg_for_errno(errbuf, PCAP_ERRBUF_SIZE,
		    lw.lw_err, "dlpi_walk");
		retv = -1;
		goto done;
	}

	/* Add linkname if it does not exist on the list. */
	for (entry = lw.lw_list; entry != NULL; entry = entry->lnl_next) {
		/*
		 * If it isn't already in the list of devices, try to
		 * add it.
		 */
		if (find_or_add_dev(devlistp, entry->linkname, 0, get_if_flags,
		    NULL, errbuf) == NULL)
			retv = -1;
	}
done:
	save_errno = errno;
	for (entry = lw.lw_list; entry != NULL; entry = next) {
		next = entry->lnl_next;
		free(entry);
	}
	errno = save_errno;

	return (retv);
}