#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  limited_rights_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int nelts; } ;
typedef  TYPE_1__ apr_array_header_t ;
struct TYPE_6__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 TYPE_3__ APR_ARRAY_IDX (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finalize_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sorted_pattern_t ; 

__attribute__((used)) static void
finalize_subnode_array(apr_array_header_t *array,
                       limited_rights_t *sum,
                       apr_pool_t *scratch_pool)
{
  if (array)
    {
      int i;
      for (i = 0; i < array->nelts; ++i)
        finalize_tree(APR_ARRAY_IDX(array, i, sorted_pattern_t).node, sum,
                      scratch_pool);
    }
}