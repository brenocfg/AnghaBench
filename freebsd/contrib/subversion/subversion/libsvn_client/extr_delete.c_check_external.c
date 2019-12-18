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
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CANNOT_DELETE_FILE_EXTERNAL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_wc__read_external_info (scalar_t__*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
check_external(const char *local_abspath,
               svn_client_ctx_t *ctx,
               apr_pool_t *scratch_pool)
{
  svn_node_kind_t external_kind;
  const char *defining_abspath;

  SVN_ERR(svn_wc__read_external_info(&external_kind, &defining_abspath, NULL,
                                     NULL, NULL,
                                     ctx->wc_ctx, local_abspath,
                                     local_abspath, TRUE,
                                     scratch_pool, scratch_pool));

  if (external_kind != svn_node_none)
    return svn_error_createf(SVN_ERR_WC_CANNOT_DELETE_FILE_EXTERNAL, NULL,
                             _("Cannot remove the external at '%s'; "
                               "please edit or delete the svn:externals "
                               "property on '%s'"),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool),
                             svn_dirent_local_style(defining_abspath,
                                                    scratch_pool));

  return SVN_NO_ERROR;
}