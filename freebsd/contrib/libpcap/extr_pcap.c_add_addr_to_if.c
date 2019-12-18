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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  pcap_if_t ;
typedef  int /*<<< orphan*/  pcap_if_list_t ;
typedef  int /*<<< orphan*/  get_if_flags_func ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;

/* Variables and functions */
 int add_addr_to_dev (int /*<<< orphan*/ *,struct sockaddr*,size_t,struct sockaddr*,size_t,struct sockaddr*,size_t,struct sockaddr*,size_t,char*) ; 
 int /*<<< orphan*/ * find_or_add_if (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
add_addr_to_if(pcap_if_list_t *devlistp, const char *name,
    bpf_u_int32 if_flags, get_if_flags_func get_flags_func,
    struct sockaddr *addr, size_t addr_size,
    struct sockaddr *netmask, size_t netmask_size,
    struct sockaddr *broadaddr, size_t broadaddr_size,
    struct sockaddr *dstaddr, size_t dstaddr_size,
    char *errbuf)
{
	pcap_if_t *curdev;

	/*
	 * Check whether the device exists and, if not, add it.
	 */
	curdev = find_or_add_if(devlistp, name, if_flags, get_flags_func,
	    errbuf);
	if (curdev == NULL) {
		/*
		 * Error - give up.
		 */
		return (-1);
	}

	if (addr == NULL) {
		/*
		 * There's no address to add; this entry just meant
		 * "here's a new interface".
		 */
		return (0);
	}

	/*
	 * "curdev" is an entry for this interface, and we have an
	 * address for it; add an entry for that address to the
	 * interface's list of addresses.
	 */
	return (add_addr_to_dev(curdev, addr, addr_size, netmask,
	    netmask_size, broadaddr, broadaddr_size, dstaddr,
	    dstaddr_size, errbuf));
}