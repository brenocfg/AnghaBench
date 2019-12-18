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
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_FILESIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  db_record_fileinfo (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_actual_props (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_op_set_props_internal(svn_wc__db_wcroot_t *wcroot,
                                 const char *local_relpath,
                                 apr_hash_t *props,
                                 svn_boolean_t clear_recorded_info,
                                 apr_pool_t *scratch_pool)
{
  SVN_ERR(set_actual_props(wcroot, local_relpath, props, scratch_pool));

  if (clear_recorded_info)
    {
      SVN_ERR(db_record_fileinfo(wcroot, local_relpath,
                                 SVN_INVALID_FILESIZE, 0,
                                 scratch_pool));
    }

  return SVN_NO_ERROR;
}