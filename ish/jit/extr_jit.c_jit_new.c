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
struct mem {int dummy; } ;
struct jit {int /*<<< orphan*/  lock; int /*<<< orphan*/  jetsam; struct mem* mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  JIT_INITIAL_HASH_SIZE ; 
 struct jit* calloc (int,int) ; 
 int /*<<< orphan*/  jit_resize_hash (struct jit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_init (int /*<<< orphan*/ *) ; 

struct jit *jit_new(struct mem *mem) {
    struct jit *jit = calloc(1, sizeof(struct jit));
    jit->mem = mem;
    jit_resize_hash(jit, JIT_INITIAL_HASH_SIZE);
    list_init(&jit->jetsam);
    lock_init(&jit->lock);
    return jit;
}