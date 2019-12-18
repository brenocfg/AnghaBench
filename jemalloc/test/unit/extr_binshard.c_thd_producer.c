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
typedef  int /*<<< orphan*/  arena ;

/* Variables and functions */
 int MALLOCX_ARENA (unsigned int) ; 
 int MALLOCX_TCACHE_NONE ; 
 int REMOTE_NALLOC ; 
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mallctl (char*,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* mallocx (int,int) ; 

__attribute__((used)) static void *
thd_producer(void *varg) {
	void **mem = varg;
	unsigned arena, i;
	size_t sz;

	sz = sizeof(arena);
	/* Remote arena. */
	assert_d_eq(mallctl("arenas.create", (void *)&arena, &sz, NULL, 0), 0,
	    "Unexpected mallctl() failure");
	for (i = 0; i < REMOTE_NALLOC / 2; i++) {
		mem[i] = mallocx(1, MALLOCX_TCACHE_NONE | MALLOCX_ARENA(arena));
	}

	/* Remote bin. */
	for (; i < REMOTE_NALLOC; i++) {
		mem[i] = mallocx(1, MALLOCX_TCACHE_NONE | MALLOCX_ARENA(0));
	}

	return NULL;
}