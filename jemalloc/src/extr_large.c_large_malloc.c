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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* large_palloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 
 size_t sz_s2u (size_t) ; 

void *
large_malloc(tsdn_t *tsdn, arena_t *arena, size_t usize, bool zero) {
	assert(usize == sz_s2u(usize));

	return large_palloc(tsdn, arena, usize, CACHELINE, zero);
}