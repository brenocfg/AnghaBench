#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_boolean_t ;
struct TYPE_9__ {size_t mem_target; TYPE_4__** freelists; TYPE_2__* stats; TYPE_1__* basic_blocks; } ;
typedef  TYPE_3__ isc__mem_t ;
struct TYPE_10__ {struct TYPE_10__* next; } ;
typedef  TYPE_4__ element ;
struct TYPE_8__ {scalar_t__ freefrags; int /*<<< orphan*/  blocks; } ;
struct TYPE_7__ {struct TYPE_7__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  more_basic_blocks (TYPE_3__*) ; 
 size_t rmsize (size_t) ; 

__attribute__((used)) static inline isc_boolean_t
more_frags(isc__mem_t *ctx, size_t new_size) {
	int i, frags;
	size_t total_size;
	void *new;
	unsigned char *curr, *next;

	/*!
	 * Try to get more fragments by chopping up a basic block.
	 */

	if (ctx->basic_blocks == NULL) {
		if (!more_basic_blocks(ctx)) {
			/*
			 * We can't get more memory from the OS, or we've
			 * hit the quota for this context.
			 */
			/*
			 * XXXRTH  "At quota" notification here.
			 */
			return (ISC_FALSE);
		}
	}

	total_size = ctx->mem_target;
	new = ctx->basic_blocks;
	ctx->basic_blocks = ctx->basic_blocks->next;
	frags = total_size / new_size;
	ctx->stats[new_size].blocks++;
	ctx->stats[new_size].freefrags += frags;
	/*
	 * Set up a linked-list of blocks of size
	 * "new_size".
	 */
	curr = new;
	next = curr + new_size;
	total_size -= new_size;
	for (i = 0; i < (frags - 1); i++) {
		((element *)curr)->next = (element *)next;
		curr = next;
		next += new_size;
		total_size -= new_size;
	}
	/*
	 * Add the remaining fragment of the basic block to a free list.
	 */
	total_size = rmsize(total_size);
	if (total_size > 0U) {
		((element *)next)->next = ctx->freelists[total_size];
		ctx->freelists[total_size] = (element *)next;
		ctx->stats[total_size].freefrags++;
	}
	/*
	 * curr is now pointing at the last block in the
	 * array.
	 */
	((element *)curr)->next = NULL;
	ctx->freelists[new_size] = new;

	return (ISC_TRUE);
}