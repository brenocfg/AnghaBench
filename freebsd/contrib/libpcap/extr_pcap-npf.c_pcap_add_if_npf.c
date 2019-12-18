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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  pcap_if_t ;
typedef  int /*<<< orphan*/  pcap_if_list_t ;
struct TYPE_3__ {int /*<<< orphan*/  Broadcast; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  IPAddress; } ;
typedef  TYPE_1__ npf_if_addr ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;
typedef  size_t LONG ;

/* Variables and functions */
 int MAX_NETWORK_ADDRESSES ; 
 int /*<<< orphan*/  PacketGetNetInfoEx (void*,TYPE_1__*,size_t*) ; 
 int add_addr_to_dev (int /*<<< orphan*/ *,struct sockaddr*,int,struct sockaddr*,int,struct sockaddr*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * add_dev (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static int
pcap_add_if_npf(pcap_if_list_t *devlistp, char *name, bpf_u_int32 flags,
    const char *description, char *errbuf)
{
	pcap_if_t *curdev;
	npf_if_addr if_addrs[MAX_NETWORK_ADDRESSES];
	LONG if_addr_size;
	int res = 0;

	if_addr_size = MAX_NETWORK_ADDRESSES;

	/*
	 * Add an entry for this interface, with no addresses.
	 */
	curdev = add_dev(devlistp, name, flags, description, errbuf);
	if (curdev == NULL) {
		/*
		 * Failure.
		 */
		return (-1);
	}

	/*
	 * Get the list of addresses for the interface.
	 */
	if (!PacketGetNetInfoEx((void *)name, if_addrs, &if_addr_size)) {
		/*
		 * Failure.
		 *
		 * We don't return an error, because this can happen with
		 * NdisWan interfaces, and we want to supply them even
		 * if we can't supply their addresses.
		 *
		 * We return an entry with an empty address list.
		 */
		return (0);
	}

	/*
	 * Now add the addresses.
	 */
	while (if_addr_size-- > 0) {
		/*
		 * "curdev" is an entry for this interface; add an entry for
		 * this address to its list of addresses.
		 */
		res = add_addr_to_dev(curdev,
		    (struct sockaddr *)&if_addrs[if_addr_size].IPAddress,
		    sizeof (struct sockaddr_storage),
		    (struct sockaddr *)&if_addrs[if_addr_size].SubnetMask,
		    sizeof (struct sockaddr_storage),
		    (struct sockaddr *)&if_addrs[if_addr_size].Broadcast,
		    sizeof (struct sockaddr_storage),
		    NULL,
		    0,
		    errbuf);
		if (res == -1) {
			/*
			 * Failure.
			 */
			break;
		}
	}

	return (res);
}