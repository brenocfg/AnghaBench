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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EXECUTABLE ; 
 int /*<<< orphan*/  SVN_PROP_NEEDS_LOCK ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_prop_get_value (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_op_add_directory (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_add_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_build_sync_file_flags (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_from_disk(svn_wc__db_t *db,
              const char *local_abspath,
              svn_node_kind_t kind,
              const apr_hash_t *props,
              apr_pool_t *scratch_pool)
{
  if (kind == svn_node_file)
    {
      svn_skel_t *work_item = NULL;

      if (props && (svn_prop_get_value(props, SVN_PROP_EXECUTABLE)
                    || svn_prop_get_value(props, SVN_PROP_NEEDS_LOCK)))
        SVN_ERR(svn_wc__wq_build_sync_file_flags(&work_item, db, local_abspath,
                                                 scratch_pool, scratch_pool));

      SVN_ERR(svn_wc__db_op_add_file(db, local_abspath, props, work_item,
                                     scratch_pool));
      if (work_item)
        SVN_ERR(svn_wc__wq_run(db, local_abspath, NULL, NULL, scratch_pool));
    }
  else
    {
      SVN_ERR(svn_wc__db_op_add_directory(db, local_abspath, props, NULL,
                                          scratch_pool));
    }

  return SVN_NO_ERROR;
}