#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  elt_size; int /*<<< orphan*/  nelts; int /*<<< orphan*/  elts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int bsearch_lower_bound (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int (*) (void const*,void const*)) ; 

int
svn_sort__bsearch_lower_bound(const apr_array_header_t *array,
                              const void *key,
                              int (*compare_func)(const void *, const void *))
{
  return bsearch_lower_bound(key,
                             array->elts, array->nelts, array->elt_size,
                             compare_func);
}