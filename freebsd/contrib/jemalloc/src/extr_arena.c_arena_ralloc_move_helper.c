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
typedef  int /*<<< orphan*/  tcache_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t LARGE_MAXCLASS ; 
 void* arena_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 void* ipalloct (int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t sz_sa2u (size_t,size_t) ; 
 int /*<<< orphan*/  sz_size2index (size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *
arena_ralloc_move_helper(tsdn_t *tsdn, arena_t *arena, size_t usize,
    size_t alignment, bool zero, tcache_t *tcache) {
	if (alignment == 0) {
		return arena_malloc(tsdn, arena, usize, sz_size2index(usize),
		    zero, tcache, true);
	}
	usize = sz_sa2u(usize, alignment);
	if (unlikely(usize == 0 || usize > LARGE_MAXCLASS)) {
		return NULL;
	}
	return ipalloct(tsdn, usize, alignment, zero, tcache, arena);
}