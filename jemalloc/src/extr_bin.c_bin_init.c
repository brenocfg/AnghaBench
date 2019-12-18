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
struct TYPE_3__ {int /*<<< orphan*/  stats; int /*<<< orphan*/  slabs_full; int /*<<< orphan*/  slabs_nonfull; int /*<<< orphan*/ * slabcur; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ bin_t ;
typedef  int /*<<< orphan*/  bin_stats_t ;

/* Variables and functions */
 int /*<<< orphan*/  WITNESS_RANK_BIN ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/  extent_heap_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_list_init (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_rank_exclusive ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bool
bin_init(bin_t *bin) {
	if (malloc_mutex_init(&bin->lock, "bin", WITNESS_RANK_BIN,
	    malloc_mutex_rank_exclusive)) {
		return true;
	}
	bin->slabcur = NULL;
	extent_heap_new(&bin->slabs_nonfull);
	extent_list_init(&bin->slabs_full);
	if (config_stats) {
		memset(&bin->stats, 0, sizeof(bin_stats_t));
	}
	return false;
}