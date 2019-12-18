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
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_4__ {int /*<<< orphan*/  nonfull_slabs; } ;
struct TYPE_5__ {TYPE_1__ stats; int /*<<< orphan*/  slabs_nonfull; } ;
typedef  TYPE_2__ bin_t ;

/* Variables and functions */
 scalar_t__ config_stats ; 
 int /*<<< orphan*/  extent_heap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_bin_slabs_nonfull_remove(bin_t *bin, extent_t *slab) {
	extent_heap_remove(&bin->slabs_nonfull, slab);
	if (config_stats) {
		bin->stats.nonfull_slabs--;
	}
}