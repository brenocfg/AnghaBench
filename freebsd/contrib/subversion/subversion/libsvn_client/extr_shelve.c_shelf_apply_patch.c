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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_patch_abspath (char**,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_patch (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
shelf_apply_patch(const char *name,
                  const char *wc_root_abspath,
                  svn_boolean_t reverse,
                  svn_boolean_t dry_run,
                  svn_client_ctx_t *ctx,
                  apr_pool_t *scratch_pool)
{
  char *patch_abspath;

  SVN_ERR(get_patch_abspath(&patch_abspath, name, wc_root_abspath,
                            ctx, scratch_pool, scratch_pool));
  SVN_ERR(svn_client_patch(patch_abspath, wc_root_abspath,
                           dry_run, 0 /*strip*/,
                           reverse,
                           FALSE /*ignore_whitespace*/,
                           TRUE /*remove_tempfiles*/, NULL, NULL,
                           ctx, scratch_pool));

  return SVN_NO_ERROR;
}