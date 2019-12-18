#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
struct TYPE_12__ {int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  local_abspath; } ;
typedef  TYPE_2__ svn_wc__committable_external_info_t ;
struct TYPE_13__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_3__* SVN_NO_ERROR ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
is_external_rolled_out(svn_boolean_t *is_rolled_out,
                       svn_wc_context_t *wc_ctx,
                       svn_wc__committable_external_info_t *xinfo,
                       apr_pool_t *scratch_pool)
{
  const char *repos_relpath;
  const char *repos_root_url;
  svn_error_t *err;

  *is_rolled_out = FALSE;

  err = svn_wc__db_base_get_info(NULL, NULL, NULL, &repos_relpath,
                                 &repos_root_url, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 wc_ctx->db, xinfo->local_abspath,
                                 scratch_pool, scratch_pool);

  if (err)
    {
      if (err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
        {
          svn_error_clear(err);
          return SVN_NO_ERROR;
        }
      SVN_ERR(err);
    }

  *is_rolled_out = (strcmp(xinfo->repos_root_url, repos_root_url) == 0 &&
                    strcmp(xinfo->repos_relpath, repos_relpath) == 0);
  return SVN_NO_ERROR;
}