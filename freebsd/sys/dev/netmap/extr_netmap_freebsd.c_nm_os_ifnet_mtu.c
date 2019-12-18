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
struct TYPE_2__ {int ifi_mtu; } ;
struct ifnet {int if_mtu; TYPE_1__ if_data; } ;

/* Variables and functions */

unsigned
nm_os_ifnet_mtu(struct ifnet *ifp)
{
#if __FreeBSD_version < 1100030
	return ifp->if_data.ifi_mtu;
#else /* __FreeBSD_version >= 1100030 */
	return ifp->if_mtu;
#endif
}