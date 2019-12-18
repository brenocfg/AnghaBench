#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_file_rename2 (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_drop_root (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_get_wcroot (char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__rename_wc(svn_wc_context_t *wc_ctx,
                  const char *from_abspath,
                  const char *dst_abspath,
                  apr_pool_t *scratch_pool)
{
  const char *wcroot_abspath;
  SVN_ERR(svn_wc__db_get_wcroot(&wcroot_abspath, wc_ctx->db, from_abspath,
                                scratch_pool, scratch_pool));

  if (! strcmp(from_abspath, wcroot_abspath))
    {
      SVN_ERR(svn_wc__db_drop_root(wc_ctx->db, wcroot_abspath, scratch_pool));

      SVN_ERR(svn_io_file_rename2(from_abspath, dst_abspath, FALSE,
                                  scratch_pool));
    }
  else
    return svn_error_createf(
                    SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                    _("'%s' is not the root of the working copy '%s'"),
                    svn_dirent_local_style(from_abspath, scratch_pool),
                    svn_dirent_local_style(wcroot_abspath, scratch_pool));

  return SVN_NO_ERROR;
}