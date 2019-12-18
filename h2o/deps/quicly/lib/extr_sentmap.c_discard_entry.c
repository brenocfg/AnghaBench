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
struct st_quicly_sent_block_t {scalar_t__ num_entries; TYPE_1__* entries; } ;
typedef  int /*<<< orphan*/  quicly_sentmap_t ;
struct TYPE_5__ {scalar_t__ count; TYPE_1__* p; struct st_quicly_sent_block_t** ref; } ;
typedef  TYPE_2__ quicly_sentmap_iter_t ;
struct TYPE_4__ {int /*<<< orphan*/ * acked; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct st_quicly_sent_block_t** free_block (int /*<<< orphan*/ *,struct st_quicly_sent_block_t**) ; 

__attribute__((used)) static void discard_entry(quicly_sentmap_t *map, quicly_sentmap_iter_t *iter)
{
    assert(iter->p->acked != NULL);
    iter->p->acked = NULL;

    struct st_quicly_sent_block_t *block = *iter->ref;
    if (--block->num_entries == 0) {
        iter->ref = free_block(map, iter->ref);
        block = *iter->ref;
        iter->p = block->entries - 1;
        iter->count = block->num_entries + 1;
    }
}