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
 size_t CACHELINE ; 
 void* large_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 
 void* large_palloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,int) ; 

__attribute__((used)) static void *
large_ralloc_move_helper(tsdn_t *tsdn, arena_t *arena, size_t usize,
    size_t alignment, bool zero) {
	if (alignment <= CACHELINE) {
		return large_malloc(tsdn, arena, usize, zero);
	}
	return large_palloc(tsdn, arena, usize, alignment, zero);
}