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
typedef  int /*<<< orphan*/  git__sort_r_cmp ;

/* Variables and functions */
 int /*<<< orphan*/  git__insertsort_r (void*,size_t,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

void git__qsort_r(
	void *els, size_t nel, size_t elsize, git__sort_r_cmp cmp, void *payload)
{
#if defined(HAVE_QSORT_R_BSD)
	git__qsort_r_glue glue = { cmp, payload };
	qsort_r(els, nel, elsize, &glue, git__qsort_r_glue_cmp);
#elif defined(HAVE_QSORT_R_GNU)
	qsort_r(els, nel, elsize, cmp, payload);
#elif defined(HAVE_QSORT_S)
	git__qsort_r_glue glue = { cmp, payload };
	qsort_s(els, nel, elsize, git__qsort_r_glue_cmp, &glue);
#else
	git__insertsort_r(els, nel, elsize, NULL, cmp, payload);
#endif
}