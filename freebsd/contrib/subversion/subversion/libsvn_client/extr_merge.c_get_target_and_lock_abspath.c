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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_wc_read_kind2 (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_target_and_lock_abspath(const char **target_abspath,
                            const char **lock_abspath,
                            const char *target_wcpath,
                            svn_client_ctx_t *ctx,
                            apr_pool_t *result_pool)
{
  svn_node_kind_t kind;
  SVN_ERR(svn_dirent_get_absolute(target_abspath, target_wcpath,
                                  result_pool));
  SVN_ERR(svn_wc_read_kind2(&kind, ctx->wc_ctx, *target_abspath,
                            FALSE, FALSE, result_pool));
  if (kind == svn_node_dir)
    *lock_abspath = *target_abspath;
  else
    *lock_abspath = svn_dirent_dirname(*target_abspath, result_pool);

  return SVN_NO_ERROR;
}