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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__internal_get_origin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__node_get_origin(svn_boolean_t *is_copy,
                        svn_revnum_t *revision,
                        const char **repos_relpath,
                        const char **repos_root_url,
                        const char **repos_uuid,
                        svn_depth_t *depth,
                        const char **copy_root_abspath,
                        svn_wc_context_t *wc_ctx,
                        const char *local_abspath,
                        svn_boolean_t scan_deleted,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  return svn_error_trace(svn_wc__internal_get_origin(is_copy, revision,
                           repos_relpath, repos_root_url, repos_uuid,
                           depth, copy_root_abspath,
                           wc_ctx->db, local_abspath, scan_deleted,
                           result_pool, scratch_pool));
}