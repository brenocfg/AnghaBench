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
typedef  int /*<<< orphan*/  svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_commit_info_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client_commit_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_client_copy2 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_copy(svn_client_commit_info_t **commit_info_p,
                const char *src_path,
                const svn_opt_revision_t *src_revision,
                const char *dst_path,
                svn_client_ctx_t *ctx,
                apr_pool_t *pool)
{
  svn_commit_info_t *commit_info = NULL;
  svn_error_t *err;

  err = svn_client_copy2(&commit_info, src_path, src_revision, dst_path,
                         ctx, pool);
  /* These structs have the same layout for the common fields. */
  *commit_info_p = (svn_client_commit_info_t *) commit_info;
  return svn_error_trace(err);
}