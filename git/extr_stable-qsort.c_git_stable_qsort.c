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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msort_with_tmp (void*,size_t,size_t,int (*) (void const*,void const*),char*) ; 
 size_t st_mult (size_t,size_t) ; 
 char* xmalloc (size_t const) ; 

void git_stable_qsort(void *b, size_t n, size_t s,
		      int (*cmp)(const void *, const void *))
{
	const size_t size = st_mult(n, s);
	char buf[1024];

	if (size < sizeof(buf)) {
		/* The temporary array fits on the small on-stack buffer. */
		msort_with_tmp(b, n, s, cmp, buf);
	} else {
		/* It's somewhat large, so malloc it.  */
		char *tmp = xmalloc(size);
		msort_with_tmp(b, n, s, cmp, tmp);
		free(tmp);
	}
}