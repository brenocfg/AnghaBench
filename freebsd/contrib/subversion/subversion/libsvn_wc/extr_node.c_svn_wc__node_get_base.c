#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
struct TYPE_14__ {char* token; } ;
typedef  TYPE_2__ svn_wc__db_lock_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_15__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_createf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 TYPE_3__* svn_wc__db_base_get_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 

svn_error_t *
svn_wc__node_get_base(svn_node_kind_t *kind,
                      svn_revnum_t *revision,
                      const char **repos_relpath,
                      const char **repos_root_url,
                      const char **repos_uuid,
                      const char **lock_token,
                      svn_wc_context_t *wc_ctx,
                      const char *local_abspath,
                      svn_boolean_t ignore_enoent,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  svn_wc__db_status_t status;
  svn_wc__db_lock_t *lock;
  svn_node_kind_t db_kind;

  err = svn_wc__db_base_get_info(&status, &db_kind, revision, repos_relpath,
                                 repos_root_url, repos_uuid, NULL,
                                 NULL, NULL, NULL, NULL, NULL,
                                 lock_token ? &lock : NULL,
                                 NULL, NULL, NULL,
                                 wc_ctx->db, local_abspath,
                                 result_pool, scratch_pool);

  if (err && err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
    return svn_error_trace(err);
  else if (err
           || (status != svn_wc__db_status_normal
               && status != svn_wc__db_status_incomplete))
    {
      if (!ignore_enoent)
        {
          if (err)
            return svn_error_trace(err);
          else
            return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                                     _("The node '%s' was not found."),
                                     svn_dirent_local_style(local_abspath,
                                                            scratch_pool));
        }
      svn_error_clear(err);

      if (kind)
        *kind = svn_node_unknown;
      if (revision)
        *revision = SVN_INVALID_REVNUM;
      if (repos_relpath)
        *repos_relpath = NULL;
      if (repos_root_url)
        *repos_root_url = NULL;
      if (repos_uuid)
        *repos_uuid = NULL;
      if (lock_token)
        *lock_token = NULL;
      return SVN_NO_ERROR;
    }

  if (kind)
    *kind = db_kind;
  if (lock_token)
    *lock_token = lock ? lock->token : NULL;

  SVN_ERR_ASSERT(!revision || SVN_IS_VALID_REVNUM(*revision));
  SVN_ERR_ASSERT(!repos_relpath || *repos_relpath);
  SVN_ERR_ASSERT(!repos_root_url || *repos_root_url);
  SVN_ERR_ASSERT(!repos_uuid || *repos_uuid);
  return SVN_NO_ERROR;
}