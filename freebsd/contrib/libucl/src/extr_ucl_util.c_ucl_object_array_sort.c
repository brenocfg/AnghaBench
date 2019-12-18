#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
struct TYPE_11__ {int /*<<< orphan*/  n; int /*<<< orphan*/  a; } ;

/* Variables and functions */
 scalar_t__ UCL_ARRAY ; 
 int /*<<< orphan*/  UCL_ARRAY_GET (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int (*) (void const*,void const*)) ; 
 TYPE_4__* vec ; 

void
ucl_object_array_sort (ucl_object_t *ar,
		int (*cmp)(const ucl_object_t **o1, const ucl_object_t **o2))
{
	UCL_ARRAY_GET (vec, ar);

	if (cmp == NULL || ar == NULL || ar->type != UCL_ARRAY) {
		return;
	}

	qsort (vec->a, vec->n, sizeof (ucl_object_t *),
			(int (*)(const void *, const void *))cmp);
}