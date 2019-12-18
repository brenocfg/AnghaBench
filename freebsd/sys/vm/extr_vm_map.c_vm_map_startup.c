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
struct vmspace {int dummy; } ;
struct vm_map_entry {int dummy; } ;
struct vm_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_KMAP ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int UMA_ZONE_MTXCLASS ; 
 int /*<<< orphan*/  UMA_ZONE_NOFREE ; 
 int UMA_ZONE_VM ; 
 void* kmapentzone ; 
 int /*<<< orphan*/  map_sleep_mtx ; 
 void* mapentzone ; 
 void* mapzone ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_prealloc (void*,int /*<<< orphan*/ ) ; 
 void* uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,...) ; 
 int /*<<< orphan*/  vm_map_zdtor ; 
 int /*<<< orphan*/  vm_map_zinit ; 
 int /*<<< orphan*/  vmspace_zdtor ; 
 int /*<<< orphan*/  vmspace_zinit ; 
 void* vmspace_zone ; 

void
vm_map_startup(void)
{
	mtx_init(&map_sleep_mtx, "vm map sleep mutex", NULL, MTX_DEF);
	mapzone = uma_zcreate("MAP", sizeof(struct vm_map), NULL,
#ifdef INVARIANTS
	    vm_map_zdtor,
#else
	    NULL,
#endif
	    vm_map_zinit, NULL, UMA_ALIGN_PTR, UMA_ZONE_NOFREE);
	uma_prealloc(mapzone, MAX_KMAP);
	kmapentzone = uma_zcreate("KMAP ENTRY", sizeof(struct vm_map_entry),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR,
	    UMA_ZONE_MTXCLASS | UMA_ZONE_VM);
	mapentzone = uma_zcreate("MAP ENTRY", sizeof(struct vm_map_entry),
	    NULL, NULL, NULL, NULL, UMA_ALIGN_PTR, 0);
	vmspace_zone = uma_zcreate("VMSPACE", sizeof(struct vmspace), NULL,
#ifdef INVARIANTS
	    vmspace_zdtor,
#else
	    NULL,
#endif
	    vmspace_zinit, NULL, UMA_ALIGN_PTR, UMA_ZONE_NOFREE);
}