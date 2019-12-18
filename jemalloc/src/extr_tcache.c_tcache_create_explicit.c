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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  tcache_t ;

/* Variables and functions */
 size_t PTR_CEILING (size_t) ; 
 int /*<<< orphan*/  TSDN_NULL ; 
 int /*<<< orphan*/  arena_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arena_ichoose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ipallocztm (int /*<<< orphan*/ ,size_t,size_t,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 size_t sz_sa2u (size_t,size_t) ; 
 int /*<<< orphan*/  tcache_arena_associate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t tcache_bin_stack_alignment (size_t) ; 
 int /*<<< orphan*/  tcache_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ total_stack_bytes ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

tcache_t *
tcache_create_explicit(tsd_t *tsd) {
	size_t size = sizeof(tcache_t);
	/* Naturally align the pointer stacks. */
	size = PTR_CEILING(size);
	size_t stack_offset = size;
	size += total_stack_bytes;
	size_t alignment = tcache_bin_stack_alignment(size);
	size = sz_sa2u(size, alignment);

	tcache_t *tcache = ipallocztm(tsd_tsdn(tsd), size, alignment, true,
	    NULL, true, arena_get(TSDN_NULL, 0, true));
	if (tcache == NULL) {
		return NULL;
	}

	void *avail_array = (void *)((uintptr_t)tcache +
	    (uintptr_t)stack_offset);
	tcache_init(tsd, tcache, avail_array);
	tcache_arena_associate(tsd_tsdn(tsd), tcache, arena_ichoose(tsd, NULL));

	return tcache;
}