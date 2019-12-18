#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  S_addr; } ;
struct TYPE_8__ {TYPE_2__ S_un; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
struct TYPE_6__ {scalar_t__ ss_family; } ;
struct TYPE_9__ {int /*<<< orphan*/  SubnetMask; TYPE_1__ IPAddress; } ;
typedef  TYPE_4__ npf_if_addr ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;
typedef  size_t LONG ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int MAX_NETWORK_ADDRESSES ; 
 int /*<<< orphan*/  PacketGetNetInfoEx (void*,TYPE_4__*,size_t*) ; 

int
pcap_lookupnet(const char *device, bpf_u_int32 *netp, bpf_u_int32 *maskp,
    char *errbuf)
{
	/*
	 * We need only the first IPv4 address, so we must scan the array returned by PacketGetNetInfo()
	 * in order to skip non IPv4 (i.e. IPv6 addresses)
	 */
	npf_if_addr if_addrs[MAX_NETWORK_ADDRESSES];
	LONG if_addr_size = MAX_NETWORK_ADDRESSES;
	struct sockaddr_in *t_addr;
	LONG i;

	if (!PacketGetNetInfoEx((void *)device, if_addrs, &if_addr_size)) {
		*netp = *maskp = 0;
		return (0);
	}

	for(i = 0; i < if_addr_size; i++)
	{
		if(if_addrs[i].IPAddress.ss_family == AF_INET)
		{
			t_addr = (struct sockaddr_in *) &(if_addrs[i].IPAddress);
			*netp = t_addr->sin_addr.S_un.S_addr;
			t_addr = (struct sockaddr_in *) &(if_addrs[i].SubnetMask);
			*maskp = t_addr->sin_addr.S_un.S_addr;

			*netp &= *maskp;
			return (0);
		}

	}

	*netp = *maskp = 0;
	return (0);
}