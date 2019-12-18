#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_16__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_NOT_DIRECTORY ; 
 int /*<<< orphan*/  SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_2__* SVN_NO_ERROR ; 
 scalar_t__ SVN_WC__ERR_IS_NOT_CURRENT_WC (TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_node_unknown ; 
 TYPE_2__* svn_wc__db_is_switched (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_read_kind (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_wclock_obtain (int /*<<< orphan*/ *,char const*,int,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__acquire_write_lock(const char **lock_root_abspath,
                           svn_wc_context_t *wc_ctx,
                           const char *local_abspath,
                           svn_boolean_t lock_anchor,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db = wc_ctx->db;
  svn_boolean_t is_wcroot;
  svn_boolean_t is_switched;
  svn_node_kind_t kind;
  svn_error_t *err;

  err = svn_wc__db_is_switched(&is_wcroot, &is_switched, &kind,
                               db, local_abspath, scratch_pool);

  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
        return svn_error_trace(err);

      svn_error_clear(err);

      kind = svn_node_none;
      is_wcroot = FALSE;
      is_switched = FALSE;
    }

  if (!lock_root_abspath && kind != svn_node_dir)
    return svn_error_createf(SVN_ERR_WC_NOT_DIRECTORY, NULL,
                             _("Can't obtain lock on non-directory '%s'."),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));

  if (lock_anchor && kind == svn_node_dir)
    {
      if (is_wcroot)
        lock_anchor = FALSE;
    }

  if (lock_anchor)
    {
      const char *parent_abspath;
      SVN_ERR_ASSERT(lock_root_abspath != NULL);

      parent_abspath = svn_dirent_dirname(local_abspath, scratch_pool);

      if (kind == svn_node_dir)
        {
          if (! is_switched)
            local_abspath = parent_abspath;
        }
      else if (kind != svn_node_none && kind != svn_node_unknown)
        {
          /* In the single-DB world we know parent exists */
          local_abspath = parent_abspath;
        }
      else
        {
          /* Can't lock parents that don't exist */
          svn_node_kind_t parent_kind;
          err = svn_wc__db_read_kind(&parent_kind, db, parent_abspath,
                                     TRUE /* allow_missing */,
                                     TRUE /* show_deleted */,
                                     FALSE /* show_hidden */,
                                     scratch_pool);
          if (err && SVN_WC__ERR_IS_NOT_CURRENT_WC(err))
            {
              svn_error_clear(err);
              parent_kind = svn_node_unknown;
            }
          else
            SVN_ERR(err);

          if (parent_kind != svn_node_dir)
            return svn_error_createf(SVN_ERR_WC_NOT_WORKING_COPY, NULL,
                                     _("'%s' is not a working copy"),
                                     svn_dirent_local_style(local_abspath,
                                                            scratch_pool));

          local_abspath = parent_abspath;
        }
    }
  else if (kind != svn_node_dir)
    {
      local_abspath = svn_dirent_dirname(local_abspath, scratch_pool);
    }

  if (lock_root_abspath)
    *lock_root_abspath = apr_pstrdup(result_pool, local_abspath);

  SVN_ERR(svn_wc__db_wclock_obtain(wc_ctx->db, local_abspath,
                                   -1 /* levels_to_lock (infinite) */,
                                   FALSE /* steal_lock */,
                                   scratch_pool));

  return SVN_NO_ERROR;
}