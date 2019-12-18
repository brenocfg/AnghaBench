#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct hotcopy_ctx_t {int src_len; scalar_t__ incremental; int /*<<< orphan*/  dest; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  (* cancel_func ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_13__ {scalar_t__ filetype; } ;
typedef  TYPE_2__ apr_finfo_t ;

/* Variables and functions */
 scalar_t__ APR_DIR ; 
 scalar_t__ APR_LNK ; 
 scalar_t__ APR_REG ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_DIR_NOT_EMPTY ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS__DB_DIR ; 
 int /*<<< orphan*/  SVN_REPOS__FORMAT ; 
 int /*<<< orphan*/  SVN_REPOS__LOCK_DIR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* create_repos_dir (char const*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_get_longest_ancestor (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 TYPE_1__* svn_io_copy_file (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_io_copy_link (char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_compare_paths (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *hotcopy_structure(void *baton,
                                      const char *path,
                                      const apr_finfo_t *finfo,
                                      apr_pool_t *pool)
{
  const struct hotcopy_ctx_t *ctx = baton;
  const char *sub_path;
  const char *target;

  if (ctx->cancel_func)
    SVN_ERR(ctx->cancel_func(ctx->cancel_baton));

  if (strlen(path) == ctx->src_len)
    {
      sub_path = "";
    }
  else
    {
      sub_path = &path[ctx->src_len+1];

      /* Check if we are inside db directory and if so skip it */
      if (svn_path_compare_paths
          (svn_dirent_get_longest_ancestor(SVN_REPOS__DB_DIR, sub_path, pool),
           SVN_REPOS__DB_DIR) == 0)
        return SVN_NO_ERROR;

      if (svn_path_compare_paths
          (svn_dirent_get_longest_ancestor(SVN_REPOS__LOCK_DIR, sub_path,
                                           pool),
           SVN_REPOS__LOCK_DIR) == 0)
        return SVN_NO_ERROR;

      if (svn_path_compare_paths
          (svn_dirent_get_longest_ancestor(SVN_REPOS__FORMAT, sub_path, pool),
           SVN_REPOS__FORMAT) == 0)
        return SVN_NO_ERROR;
    }

  target = svn_dirent_join(ctx->dest, sub_path, pool);

  if (finfo->filetype == APR_DIR)
    {
      svn_error_t *err;

      err = create_repos_dir(target, pool);
      if (ctx->incremental && err && err->apr_err == SVN_ERR_DIR_NOT_EMPTY)
        {
          svn_error_clear(err);
          err = SVN_NO_ERROR;
        }
      return svn_error_trace(err);
    }
  else if (finfo->filetype == APR_REG)
    return svn_io_copy_file(path, target, TRUE, pool);
  else if (finfo->filetype == APR_LNK)
    return svn_io_copy_link(path, target, pool);
  else
    return SVN_NO_ERROR;
}