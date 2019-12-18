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
 int ENOMEM ; 
 int /*<<< orphan*/  NM_BRIDGES ; 
 int netmap_bns_register () ; 
 int /*<<< orphan*/ * netmap_init_bridges2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nm_bridges ; 

int
netmap_init_bridges(void)
{
#ifdef CONFIG_NET_NS
	return netmap_bns_register();
#else
	nm_bridges = netmap_init_bridges2(NM_BRIDGES);
	if (nm_bridges == NULL)
		return ENOMEM;
	return 0;
#endif
}