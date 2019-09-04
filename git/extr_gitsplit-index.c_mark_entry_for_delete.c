#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct index_state {size_t cache_nr; TYPE_2__* split_index; TYPE_1__** cache; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr_deletions; } ;
struct TYPE_3__ {int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_REMOVE ; 
 int /*<<< orphan*/  die (char*,int,size_t) ; 

__attribute__((used)) static void mark_entry_for_delete(size_t pos, void *data)
{
	struct index_state *istate = data;
	if (pos >= istate->cache_nr)
		die("position for delete %d exceeds base index size %d",
		    (int)pos, istate->cache_nr);
	istate->cache[pos]->ce_flags |= CE_REMOVE;
	istate->split_index->nr_deletions++;
}