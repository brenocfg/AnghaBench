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
struct load_cache_entries_thread_data {int ieot_start; int ieot_blocks; TYPE_2__* ieot; int /*<<< orphan*/  offset; int /*<<< orphan*/  mmap; int /*<<< orphan*/  ce_mem_pool; int /*<<< orphan*/  istate; int /*<<< orphan*/  consumed; } ;
struct TYPE_4__ {TYPE_1__* entries; } ;
struct TYPE_3__ {scalar_t__ nr; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 scalar_t__ load_cache_entry_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *load_cache_entries_thread(void *_data)
{
	struct load_cache_entries_thread_data *p = _data;
	int i;

	/* iterate across all ieot blocks assigned to this thread */
	for (i = p->ieot_start; i < p->ieot_start + p->ieot_blocks; i++) {
		p->consumed += load_cache_entry_block(p->istate, p->ce_mem_pool,
			p->offset, p->ieot->entries[i].nr, p->mmap, p->ieot->entries[i].offset, NULL);
		p->offset += p->ieot->entries[i].nr;
	}
	return NULL;
}