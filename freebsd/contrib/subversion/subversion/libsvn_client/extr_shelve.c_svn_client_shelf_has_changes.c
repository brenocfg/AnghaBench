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
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_shelf_get_paths (int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_shelf_has_changes(svn_boolean_t *has_changes,
                             const char *name,
                             const char *local_abspath,
                             svn_client_ctx_t *ctx,
                             apr_pool_t *scratch_pool)
{
  apr_hash_t *patch_paths;

  SVN_ERR(svn_client_shelf_get_paths(&patch_paths, name, local_abspath,
                                     ctx, scratch_pool, scratch_pool));
  *has_changes = (apr_hash_count(patch_paths) != 0);
  return SVN_NO_ERROR;
}