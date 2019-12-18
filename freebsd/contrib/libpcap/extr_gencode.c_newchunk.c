#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct chunk {size_t n_left; int /*<<< orphan*/ * m; } ;
struct TYPE_4__ {size_t cur_chunk; struct chunk* chunks; } ;
typedef  TYPE_1__ compiler_state_t ;

/* Variables and functions */
 size_t ALIGN (size_t) ; 
 int CHUNK0SIZE ; 
 int NCHUNKS ; 
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void *
newchunk(compiler_state_t *cstate, size_t n)
{
	struct chunk *cp;
	int k;
	size_t size;

#ifndef __NetBSD__
	/* XXX Round up to nearest long. */
	n = (n + sizeof(long) - 1) & ~(sizeof(long) - 1);
#else
	/* XXX Round up to structure boundary. */
	n = ALIGN(n);
#endif

	cp = &cstate->chunks[cstate->cur_chunk];
	if (n > cp->n_left) {
		++cp;
		k = ++cstate->cur_chunk;
		if (k >= NCHUNKS)
			bpf_error(cstate, "out of memory");
		size = CHUNK0SIZE << k;
		cp->m = (void *)malloc(size);
		if (cp->m == NULL)
			bpf_error(cstate, "out of memory");
		memset((char *)cp->m, 0, size);
		cp->n_left = size;
		if (n > size)
			bpf_error(cstate, "out of memory");
	}
	cp->n_left -= n;
	return (void *)((char *)cp->m + cp->n_left);
}