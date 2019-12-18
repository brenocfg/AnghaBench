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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_wc__db_external_add_dir (int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__external_register(svn_wc_context_t *wc_ctx,
                          const char *defining_abspath,
                          const char *local_abspath,
                          svn_node_kind_t kind,
                          const char *repos_root_url,
                          const char *repos_uuid,
                          const char *repos_relpath,
                          svn_revnum_t operational_revision,
                          svn_revnum_t revision,
                          apr_pool_t *scratch_pool)
{
  SVN_ERR_ASSERT(kind == svn_node_dir);
  return svn_error_trace(
            svn_wc__db_external_add_dir(wc_ctx->db, local_abspath,
                                        defining_abspath,
                                        repos_root_url,
                                        repos_uuid,
                                        defining_abspath,
                                        repos_relpath,
                                        operational_revision,
                                        revision,
                                        NULL,
                                        scratch_pool));
}