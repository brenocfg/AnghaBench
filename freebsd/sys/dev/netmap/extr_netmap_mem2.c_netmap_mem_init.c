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
 int /*<<< orphan*/  NMA_LOCK_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NM_MTX_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netmap_mem_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_mem ; 
 int /*<<< orphan*/  nm_mem_ext_list_lock ; 
 int /*<<< orphan*/  nm_mem_list_lock ; 

int
netmap_mem_init(void)
{
	NM_MTX_INIT(nm_mem_list_lock);
	NMA_LOCK_INIT(&nm_mem);
	netmap_mem_get(&nm_mem);
#ifdef WITH_EXTMEM
	NM_MTX_INIT(nm_mem_ext_list_lock);
#endif /* WITH_EXTMEM */
	return (0);
}