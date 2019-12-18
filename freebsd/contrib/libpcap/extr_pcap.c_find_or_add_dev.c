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
typedef  int /*<<< orphan*/  pcap_if_t ;
typedef  int /*<<< orphan*/  pcap_if_list_t ;
typedef  int (* get_if_flags_func ) (char const*,int /*<<< orphan*/ *,char*) ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;

/* Variables and functions */
 int /*<<< orphan*/ * add_dev (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/ * find_dev (int /*<<< orphan*/ *,char const*) ; 
 int stub1 (char const*,int /*<<< orphan*/ *,char*) ; 

pcap_if_t *
find_or_add_dev(pcap_if_list_t *devlistp, const char *name, bpf_u_int32 flags,
    get_if_flags_func get_flags_func, const char *description, char *errbuf)
{
	pcap_if_t *curdev;

	/*
	 * Is there already an entry in the list for this device?
	 */
	curdev = find_dev(devlistp, name);
	if (curdev != NULL) {
		/*
		 * Yes, return it.
		 */
		return (curdev);
	}

	/*
	 * No, we didn't find it.
	 */

	/*
	 * Try to get additional flags for the device.
	 */
	if ((*get_flags_func)(name, &flags, errbuf) == -1) {
		/*
		 * Failed.
		 */
		return (NULL);
	}

	/*
	 * Now, try to add it to the list of devices.
	 */
	return (add_dev(devlistp, name, flags, description, errbuf));
}