#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* git__sort_r_cmp ;
struct TYPE_7__ {void* member_1; struct TYPE_7__* member_0; } ;
typedef  TYPE_1__ git__qsort_r_glue ;

/* Variables and functions */
 void* git__qsort_r_glue_cmp ; 
 int /*<<< orphan*/  insertsort (void*,size_t,size_t,TYPE_1__*,void*) ; 
 int /*<<< orphan*/  qsort_r (void*,size_t,size_t,TYPE_1__*,void*) ; 
 int /*<<< orphan*/  qsort_s (void*,size_t,size_t,void*,TYPE_1__*) ; 

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
	insertsort(els, nel, elsize, cmp, payload);
#endif
}