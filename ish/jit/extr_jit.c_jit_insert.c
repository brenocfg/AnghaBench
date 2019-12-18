#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct jit_block {size_t addr; size_t end_addr; int /*<<< orphan*/ * page; int /*<<< orphan*/  chain; scalar_t__ used; } ;
struct jit {int num_blocks; int hash_size; int /*<<< orphan*/  mem; int /*<<< orphan*/ * hash; int /*<<< orphan*/  mem_used; } ;

/* Variables and functions */
 scalar_t__ PAGE (size_t) ; 
 int /*<<< orphan*/ * blocks_list (struct jit*,scalar_t__,int) ; 
 int /*<<< orphan*/  jit_resize_hash (struct jit*,int) ; 
 int /*<<< orphan*/  list_init_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mem_pt (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void jit_insert(struct jit *jit, struct jit_block *block) {
    jit->mem_used += block->used;
    jit->num_blocks++;
    // target an average hash chain length of 1-2
    if (jit->num_blocks >= jit->hash_size * 2)
        jit_resize_hash(jit, jit->hash_size * 2);

    list_init_add(&jit->hash[block->addr % jit->hash_size], &block->chain);
    if (mem_pt(jit->mem, PAGE(block->addr)) == NULL)
        return;
    list_init_add(blocks_list(jit, PAGE(block->addr), 0), &block->page[0]);
    if (PAGE(block->addr) != PAGE(block->end_addr))
        list_init_add(blocks_list(jit, PAGE(block->end_addr), 1), &block->page[1]);
}