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
struct vmem_btag {int dummy; } ;
struct vmem {int dummy; } ;

/* Variables and functions */
 int BT_MAXALLOC ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int UMA_ZONE_NOFREE ; 
 int UMA_ZONE_VM ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_prealloc (void*,int) ; 
 void* uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_zone_reserve (void*,int) ; 
 int /*<<< orphan*/  uma_zone_set_allocf (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_bt_alloc ; 
 int /*<<< orphan*/  vmem_bt_lock ; 
 void* vmem_bt_zone ; 
 int /*<<< orphan*/  vmem_list_lock ; 
 void* vmem_zone ; 

void
vmem_startup(void)
{

	mtx_init(&vmem_list_lock, "vmem list lock", NULL, MTX_DEF);
	vmem_zone = uma_zcreate("vmem",
	    sizeof(struct vmem), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, UMA_ZONE_VM);
	vmem_bt_zone = uma_zcreate("vmem btag",
	    sizeof(struct vmem_btag), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, UMA_ZONE_VM | UMA_ZONE_NOFREE);
#ifndef UMA_MD_SMALL_ALLOC
	mtx_init(&vmem_bt_lock, "btag lock", NULL, MTX_DEF);
	uma_prealloc(vmem_bt_zone, BT_MAXALLOC);
	/*
	 * Reserve enough tags to allocate new tags.  We allow multiple
	 * CPUs to attempt to allocate new tags concurrently to limit
	 * false restarts in UMA.  vmem_bt_alloc() allocates from a per-domain
	 * arena, which may involve importing a range from the kernel arena,
	 * so we need to keep at least 2 * BT_MAXALLOC tags reserved.
	 */
	uma_zone_reserve(vmem_bt_zone, 2 * BT_MAXALLOC * mp_ncpus);
	uma_zone_set_allocf(vmem_bt_zone, vmem_bt_alloc);
#endif
}