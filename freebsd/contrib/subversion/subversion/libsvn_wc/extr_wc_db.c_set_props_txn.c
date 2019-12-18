#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_9__ {scalar_t__ nelts; } ;
typedef  TYPE_2__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_work_items (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_read_pristine_props (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_diffs (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_mark_conflict_internal (TYPE_1__*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_set_props_internal (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
set_props_txn(svn_wc__db_wcroot_t *wcroot,
              const char *local_relpath,
              apr_hash_t *props,
              svn_boolean_t clear_recorded_info,
              const svn_skel_t *conflict,
              const svn_skel_t *work_items,
              apr_pool_t *scratch_pool)
{
  apr_hash_t *pristine_props;

  /* Check if the props are modified. If no changes, then wipe out the
     ACTUAL props.  PRISTINE_PROPS==NULL means that any
     ACTUAL props are okay as provided, so go ahead and set them.  */
  SVN_ERR(db_read_pristine_props(&pristine_props, wcroot, local_relpath, FALSE,
                                 scratch_pool, scratch_pool));
  if (props && pristine_props)
    {
      apr_array_header_t *prop_diffs;

      SVN_ERR(svn_prop_diffs(&prop_diffs, props, pristine_props,
                             scratch_pool));
      if (prop_diffs->nelts == 0)
        props = NULL;
    }

  SVN_ERR(svn_wc__db_op_set_props_internal(wcroot, local_relpath, props,
                                           clear_recorded_info, scratch_pool));

  /* And finally.  */
  SVN_ERR(add_work_items(wcroot->sdb, work_items, scratch_pool));
  if (conflict)
    SVN_ERR(svn_wc__db_mark_conflict_internal(wcroot, local_relpath,
                                              conflict, scratch_pool));

  return SVN_NO_ERROR;
}