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
typedef  int /*<<< orphan*/  h ;
typedef  int /*<<< orphan*/  extent_hooks_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mallctl (char*,void*,size_t*,void*,int) ; 

__attribute__((used)) static unsigned
do_arena_create(extent_hooks_t *h) {
	unsigned arena_ind;
	size_t sz = sizeof(unsigned);
	assert_d_eq(mallctl("arenas.create", (void *)&arena_ind, &sz,
	    (void *)(h != NULL ? &h : NULL), (h != NULL ? sizeof(h) : 0)), 0,
	    "Unexpected mallctl() failure");
	return arena_ind;
}