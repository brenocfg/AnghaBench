#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pcap_if_t ;
struct TYPE_5__ {int /*<<< orphan*/ * beginning; } ;
typedef  TYPE_1__ pcap_if_list_t ;
struct TYPE_6__ {int (* findalldevs_op ) (TYPE_1__*,char*) ;} ;

/* Variables and functions */
 TYPE_4__* capture_source_types ; 
 int /*<<< orphan*/  pcap_freealldevs (int /*<<< orphan*/ *) ; 
 int pcap_platform_finddevs (TYPE_1__*,char*) ; 
 int stub1 (TYPE_1__*,char*) ; 

int
pcap_findalldevs(pcap_if_t **alldevsp, char *errbuf)
{
	size_t i;
	pcap_if_list_t devlist;

	/*
	 * Find all the local network interfaces on which we
	 * can capture.
	 */
	devlist.beginning = NULL;
	if (pcap_platform_finddevs(&devlist, errbuf) == -1) {
		/*
		 * Failed - free all of the entries we were given
		 * before we failed.
		 */
		if (devlist.beginning != NULL)
			pcap_freealldevs(devlist.beginning);
		*alldevsp = NULL;
		return (-1);
	}

	/*
	 * Ask each of the non-local-network-interface capture
	 * source types what interfaces they have.
	 */
	for (i = 0; capture_source_types[i].findalldevs_op != NULL; i++) {
		if (capture_source_types[i].findalldevs_op(&devlist, errbuf) == -1) {
			/*
			 * We had an error; free the list we've been
			 * constructing.
			 */
			if (devlist.beginning != NULL)
				pcap_freealldevs(devlist.beginning);
			*alldevsp = NULL;
			return (-1);
		}
	}

	/*
	 * Return the first entry of the list of all devices.
	 */
	*alldevsp = devlist.beginning;
	return (0);
}