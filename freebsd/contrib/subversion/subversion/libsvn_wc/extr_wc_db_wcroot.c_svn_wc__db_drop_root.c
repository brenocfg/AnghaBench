#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
struct TYPE_8__ {int /*<<< orphan*/  state_pool; int /*<<< orphan*/  dir_data; } ;
typedef  TYPE_2__ svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_ERR_WC_NOT_WORKING_COPY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_pool_cleanup_run (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_wcroot ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_drop_root(svn_wc__db_t *db,
                     const char *local_abspath,
                     apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *root_wcroot = svn_hash_gets(db->dir_data, local_abspath);
  apr_hash_index_t *hi;
  apr_status_t result;

  if (!root_wcroot)
    return SVN_NO_ERROR;

  if (strcmp(root_wcroot->abspath, local_abspath) != 0)
    return svn_error_createf(SVN_ERR_WC_NOT_WORKING_COPY, NULL,
                             _("'%s' is not a working copy root"),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));

  for (hi = apr_hash_first(scratch_pool, db->dir_data);
       hi;
       hi = apr_hash_next(hi))
    {
      svn_wc__db_wcroot_t *wcroot = apr_hash_this_val(hi);

      if (wcroot == root_wcroot)
        svn_hash_sets(db->dir_data, apr_hash_this_key(hi), NULL);
    }

  result = apr_pool_cleanup_run(db->state_pool, root_wcroot, close_wcroot);
  if (result != APR_SUCCESS)
    return svn_error_wrap_apr(result, NULL);

  return SVN_NO_ERROR;
}