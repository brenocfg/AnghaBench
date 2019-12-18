#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* children; int /*<<< orphan*/  is_atom; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_WC__SINGLE_WORK_ITEM (TYPE_1__ const*) ; 
 int /*<<< orphan*/  add_single_work_item (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_work_items(svn_sqlite__db_t *sdb,
               const svn_skel_t *skel,
               apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool;

  /* Maybe there are no work items to insert.  */
  if (skel == NULL)
    return SVN_NO_ERROR;

  /* Should have a list.  */
  SVN_ERR_ASSERT(!skel->is_atom);

  /* Is the list a single work item? Or a list of work items?  */
  if (SVN_WC__SINGLE_WORK_ITEM(skel))
    return svn_error_trace(add_single_work_item(sdb, skel, scratch_pool));

  /* SKEL is a list-of-lists, aka list of work items.  */

  iterpool = svn_pool_create(scratch_pool);
  for (skel = skel->children; skel; skel = skel->next)
    {
      svn_pool_clear(iterpool);

      SVN_ERR(add_single_work_item(sdb, skel, iterpool));
    }
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}