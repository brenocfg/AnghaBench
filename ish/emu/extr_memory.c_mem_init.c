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
struct pt_entry {int dummy; } ;
struct mem {int /*<<< orphan*/  lock; int /*<<< orphan*/  jit; scalar_t__ changes; scalar_t__ pgdir_used; int /*<<< orphan*/  pgdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_PGDIR_SIZE ; 
 int /*<<< orphan*/  calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jit_new (struct mem*) ; 
 int /*<<< orphan*/  wrlock_init (int /*<<< orphan*/ *) ; 

void mem_init(struct mem *mem) {
    mem->pgdir = calloc(MEM_PGDIR_SIZE, sizeof(struct pt_entry *));
    mem->pgdir_used = 0;
    mem->changes = 0;
#if ENGINE_JIT
    mem->jit = jit_new(mem);
#endif
    wrlock_init(&mem->lock);
}