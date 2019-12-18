#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  swap ;
struct kvm_swap {scalar_t__ ksw_used; scalar_t__ ksw_total; } ;
struct TYPE_5__ {int memActive; int memWire; int memZfsArc; int /*<<< orphan*/  kd; scalar_t__ zfsArcEnabled; } ;
struct TYPE_4__ {int totalMem; int buffersMem; int cachedMem; int usedMem; int totalSwap; int usedSwap; scalar_t__ sharedMem; } ;
typedef  TYPE_1__ ProcessList ;
typedef  TYPE_2__ FreeBSDProcessList ;

/* Variables and functions */
 int /*<<< orphan*/  MIB_hw_physmem ; 
 int /*<<< orphan*/  MIB_kstat_zfs_misc_arcstats_size ; 
 int /*<<< orphan*/  MIB_vfs_bufspace ; 
 int /*<<< orphan*/  MIB_vm_stats_vm_v_active_count ; 
 int /*<<< orphan*/  MIB_vm_stats_vm_v_cache_count ; 
 int /*<<< orphan*/  MIB_vm_stats_vm_v_wire_count ; 
 int kvm_getswapinfo (int /*<<< orphan*/ ,struct kvm_swap*,int,int /*<<< orphan*/ ) ; 
 int pageSizeKb ; 
 int /*<<< orphan*/  sysctl (int /*<<< orphan*/ ,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void FreeBSDProcessList_scanMemoryInfo(ProcessList* pl) {
   FreeBSDProcessList* fpl = (FreeBSDProcessList*) pl;

   // @etosan:
   // memory counter relationships seem to be these:
   //  total = active + wired + inactive + cache + free
   //  htop_used (unavail to anybody) = active + wired
   //  htop_cache (for cache meter)   = buffers + cache
   //  user_free (avail to procs)     = buffers + inactive + cache + free
   //
   // with ZFS ARC situation becomes bit muddled, as ARC behaves like "user_free"
   // and belongs into cache, but is reported as wired by kernel
   //
   // htop_used   = active + (wired - arc)
   // htop_cache  = buffers + cache + arc
   size_t len = sizeof(pl->totalMem);

   //disabled for now, as it is always smaller than phycal amount of memory...
   //...to avoid "where is my memory?" questions
   //sysctl(MIB_vm_stats_vm_v_page_count, 4, &(pl->totalMem), &len, NULL, 0);
   //pl->totalMem *= pageSizeKb;
   sysctl(MIB_hw_physmem, 2, &(pl->totalMem), &len, NULL, 0);
   pl->totalMem /= 1024;

   sysctl(MIB_vm_stats_vm_v_active_count, 4, &(fpl->memActive), &len, NULL, 0);
   fpl->memActive *= pageSizeKb;

   sysctl(MIB_vm_stats_vm_v_wire_count, 4, &(fpl->memWire), &len, NULL, 0);
   fpl->memWire *= pageSizeKb;

   sysctl(MIB_vfs_bufspace, 2, &(pl->buffersMem), &len, NULL, 0);
   pl->buffersMem /= 1024;

   sysctl(MIB_vm_stats_vm_v_cache_count, 4, &(pl->cachedMem), &len, NULL, 0);
   pl->cachedMem *= pageSizeKb;

   if (fpl->zfsArcEnabled) {
      len = sizeof(fpl->memZfsArc);
      sysctl(MIB_kstat_zfs_misc_arcstats_size, 5, &(fpl->memZfsArc), &len , NULL, 0);
      fpl->memZfsArc /= 1024;
      fpl->memWire -= fpl->memZfsArc;
      pl->cachedMem += fpl->memZfsArc;
      // maybe when we learn how to make custom memory meter
      // we could do custom arc breakdown?
   }

   pl->usedMem = fpl->memActive + fpl->memWire;

   //currently unused, same as with arc, custom meter perhaps
   //sysctl(MIB_vm_stats_vm_v_inactive_count, 4, &(fpl->memInactive), &len, NULL, 0);
   //sysctl(MIB_vm_stats_vm_v_free_count, 4, &(fpl->memFree), &len, NULL, 0);
   //pl->freeMem  = fpl->memInactive + fpl->memFree;
   //pl->freeMem *= pageSizeKb;

   struct kvm_swap swap[16];
   int nswap = kvm_getswapinfo(fpl->kd, swap, sizeof(swap)/sizeof(swap[0]), 0);
   pl->totalSwap = 0;
   pl->usedSwap = 0;
   for (int i = 0; i < nswap; i++) {
      pl->totalSwap += swap[i].ksw_total;
      pl->usedSwap += swap[i].ksw_used;
   }
   pl->totalSwap *= pageSizeKb;
   pl->usedSwap *= pageSizeKb;

   pl->sharedMem = 0;  // currently unused
}