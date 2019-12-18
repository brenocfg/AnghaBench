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
struct TYPE_5__ {int /*<<< orphan*/  name; struct TYPE_5__* next; } ;
typedef  TYPE_1__ pcap_if_t ;
struct TYPE_6__ {TYPE_1__* beginning; } ;
typedef  TYPE_2__ pcap_if_list_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

pcap_if_t *
find_dev(pcap_if_list_t *devlistp, const char *name)
{
	pcap_if_t *curdev;

	/*
	 * Is there an entry in the list for this device?
	 */
	for (curdev = devlistp->beginning; curdev != NULL;
	    curdev = curdev->next) {
		if (strcmp(name, curdev->name) == 0) {
			/*
			 * We found it, so, yes, there is.  No need to
			 * add it.  Provide the entry we found to our
			 * caller.
			 */
			return (curdev);
		}
	}

	/*
	 * No.
	 */
	return (NULL);
}