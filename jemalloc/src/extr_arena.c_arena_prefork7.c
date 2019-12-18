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
struct TYPE_6__ {TYPE_1__* bins; } ;
typedef  TYPE_2__ arena_t ;
struct TYPE_7__ {unsigned int n_shards; } ;
struct TYPE_5__ {int /*<<< orphan*/ * bin_shards; } ;

/* Variables and functions */
 unsigned int SC_NBINS ; 
 TYPE_3__* bin_infos ; 
 int /*<<< orphan*/  bin_prefork (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
arena_prefork7(tsdn_t *tsdn, arena_t *arena) {
	for (unsigned i = 0; i < SC_NBINS; i++) {
		for (unsigned j = 0; j < bin_infos[i].n_shards; j++) {
			bin_prefork(tsdn, &arena->bins[i].bin_shards[j]);
		}
	}
}