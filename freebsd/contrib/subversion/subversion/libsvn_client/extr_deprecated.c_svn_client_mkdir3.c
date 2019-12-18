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
typedef  int /*<<< orphan*/  svn_commit_info_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct capture_baton_t {int /*<<< orphan*/ * pool; int /*<<< orphan*/ ** info; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  capture_commit_info ; 
 int /*<<< orphan*/ * svn_client_mkdir4 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct capture_baton_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_mkdir3(svn_commit_info_t **commit_info_p,
                  const apr_array_header_t *paths,
                  svn_boolean_t make_parents,
                  const apr_hash_t *revprop_table,
                  svn_client_ctx_t *ctx,
                  apr_pool_t *pool)
{
  struct capture_baton_t cb;

  cb.info = commit_info_p;
  cb.pool = pool;

  return svn_client_mkdir4(paths, make_parents, revprop_table,
                           capture_commit_info, &cb, ctx, pool);
}