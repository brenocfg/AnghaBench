#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  path_order_t ;
struct TYPE_5__ {TYPE_2__* path_order; int /*<<< orphan*/  info_pool; TYPE_2__* references; } ;
typedef  TYPE_1__ pack_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {scalar_t__ nelts; scalar_t__ elts; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  classify_nodes (int /*<<< orphan*/ **,int) ; 
 scalar_t__ compare_path_order ; 
 scalar_t__ compare_references ; 
 int /*<<< orphan*/  sort_reps_range (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sort__array (TYPE_2__*,int (*) (void const*,void const*)) ; 

__attribute__((used)) static void
sort_reps(pack_context_t *context)
{
  apr_pool_t *temp_pool;
  path_order_t **temp, **path_order;
  int i, count;

  /* We will later assume that there is at least one node / path.
   */
  if (context->path_order->nelts == 0)
    {
      assert(context->references->nelts == 0);
      return;
    }

  /* Sort containers by path and IDs, respectively.
   */
  svn_sort__array(context->path_order,
                  (int (*)(const void *, const void *))compare_path_order);
  svn_sort__array(context->references,
                  (int (*)(const void *, const void *))compare_references);

  /* Directories are already in front; sort directories section and files
   * section separately but use the same heuristics (see sub-function).
   */
  temp_pool = svn_pool_create(context->info_pool);
  count = context->path_order->nelts;
  temp = apr_pcalloc(temp_pool, count * sizeof(*temp));
  path_order = (void *)context->path_order->elts;

  /* Mark nodes depending on what other nodes exist for the same path etc. */
  classify_nodes(path_order, count);

  /* Rearrange those sub-sections separately. */
  sort_reps_range(context, path_order, temp, 0, count);

  /* We now know the final ordering. */
  for (i = 0; i < count; ++i)
    path_order[i] = temp[i];

  svn_pool_destroy(temp_pool);
}