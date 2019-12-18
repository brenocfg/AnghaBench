#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_2__ {int /*<<< orphan*/ * macs; } ;
struct vtnet_mac_filter {TYPE_1__ vmf_multicast; } ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 size_t VTNET_MAX_MAC_ENTRIES ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
vtnet_copy_maddr(void *arg, struct sockaddr_dl *sdl, u_int mcnt)
{
	struct vtnet_mac_filter *filter = arg;

	if (mcnt < VTNET_MAX_MAC_ENTRIES)
		bcopy(LLADDR(sdl), &filter->vmf_multicast.macs[mcnt],
		    ETHER_ADDR_LEN);

	return (1);
}