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

/* Variables and functions */
 int /*<<< orphan*/  NM_BRIDGES ; 
 int /*<<< orphan*/  netmap_bns_unregister () ; 
 int /*<<< orphan*/  netmap_uninit_bridges2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_bridges ; 

void
netmap_uninit_bridges(void)
{
#ifdef CONFIG_NET_NS
	netmap_bns_unregister();
#else
	netmap_uninit_bridges2(nm_bridges, NM_BRIDGES);
#endif
}