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
typedef  int /*<<< orphan*/  stats_buffer_t ;
struct TYPE_3__ {int /*<<< orphan*/  swap_total; int /*<<< orphan*/  swap_used; int /*<<< orphan*/  mem_free; int /*<<< orphan*/  vm_data; int /*<<< orphan*/  vm_rss; int /*<<< orphan*/  vm_size; } ;
typedef  TYPE_1__ am_memory_stat_t ;

/* Variables and functions */
 int AM_GET_MEMORY_USAGE_OVERALL ; 
 int AM_GET_MEMORY_USAGE_SELF ; 
 int /*<<< orphan*/  am_get_memory_stats (TYPE_1__*,int) ; 
 scalar_t__ dyn_cur ; 
 scalar_t__ dyn_first ; 
 scalar_t__ dyn_last ; 
 scalar_t__ dyn_top ; 
 int /*<<< orphan*/  dyn_update_stats () ; 
 int /*<<< orphan*/  freed_blocks ; 
 int /*<<< orphan*/  freed_bytes ; 
 int /*<<< orphan*/  sb_printf (int /*<<< orphan*/ *,char*,long,long,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wasted_blocks ; 
 int /*<<< orphan*/  wasted_bytes ; 

void sb_memory (stats_buffer_t *sb, int flags) {
  dyn_update_stats ();
  sb_printf (sb,
    "heap_allocated\t%ld\n"
    "heap_max\t%ld\n"
    "wasted_heap_blocks\t%d\n"
    "wasted_heap_bytes\t%ld\n"
    "free_heap_blocks\t%d\n"
    "free_heap_bytes\t%ld\n",
    (long)(dyn_cur - dyn_first) + (long) (dyn_last - dyn_top),
    (long)(dyn_last - dyn_first),
    wasted_blocks,
    wasted_bytes,
    freed_blocks,
    freed_bytes);

  am_memory_stat_t S;
  if (!am_get_memory_stats (&S, flags & AM_GET_MEMORY_USAGE_SELF)) {
    sb_printf (sb,
      "vmsize_bytes\t%lld\n"
      "vmrss_bytes\t%lld\n"
      "vmdata_bytes\t%lld\n",
    S.vm_size, S.vm_rss, S.vm_data);
  }

  if (!am_get_memory_stats (&S, flags & AM_GET_MEMORY_USAGE_OVERALL)) {
    sb_printf (sb,
        "memfree_bytes\t%lld\n"
        "swap_used_bytes\t%lld\n"
        "swap_total_bytes\t%lld\n",
    S.mem_free, S.swap_used, S.swap_total);
  }
}