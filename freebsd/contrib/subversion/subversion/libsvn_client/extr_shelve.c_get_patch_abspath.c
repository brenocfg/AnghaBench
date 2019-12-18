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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shelf_name_encode (char**,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__get_shelves_dir (char**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_patch_abspath(char **patch_abspath,
                  const char *name,
                  const char *wc_root_abspath,
                  svn_client_ctx_t *ctx,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  char *dir;
  char *filename;

  SVN_ERR(svn_wc__get_shelves_dir(&dir, ctx->wc_ctx, wc_root_abspath,
                                  scratch_pool, scratch_pool));
  SVN_ERR(shelf_name_encode(&filename, name, scratch_pool));
  filename = apr_pstrcat(scratch_pool, filename, ".patch", SVN_VA_NULL);
  *patch_abspath = svn_dirent_join(dir, filename, result_pool);
  return SVN_NO_ERROR;
}