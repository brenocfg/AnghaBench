#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  scalar_t__ szind_t ;
struct TYPE_7__ {TYPE_1__* lstats; } ;
struct TYPE_6__ {TYPE_3__ stats; } ;
typedef  TYPE_2__ arena_t ;
struct TYPE_5__ {int /*<<< orphan*/  nmalloc; } ;

/* Variables and functions */
 size_t LARGE_MINCLASS ; 
 scalar_t__ NBINS ; 
 int /*<<< orphan*/  arena_stats_add_u64 (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_stats ; 
 scalar_t__ sz_size2index (size_t) ; 

__attribute__((used)) static void
arena_large_malloc_stats_update(tsdn_t *tsdn, arena_t *arena, size_t usize) {
	szind_t index, hindex;

	cassert(config_stats);

	if (usize < LARGE_MINCLASS) {
		usize = LARGE_MINCLASS;
	}
	index = sz_size2index(usize);
	hindex = (index >= NBINS) ? index - NBINS : 0;

	arena_stats_add_u64(tsdn, &arena->stats,
	    &arena->stats.lstats[hindex].nmalloc, 1);
}