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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_client_add5 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_dir_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_make_dir_recursively (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 

svn_error_t *
svn_client__make_local_parents(const char *local_abspath,
                               svn_boolean_t make_parents,
                               svn_client_ctx_t *ctx,
                               apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  svn_node_kind_t orig_kind;
  SVN_ERR(svn_io_check_path(local_abspath, &orig_kind, scratch_pool));
  if (make_parents)
    SVN_ERR(svn_io_make_dir_recursively(local_abspath, scratch_pool));
  else
    SVN_ERR(svn_io_dir_make(local_abspath, APR_OS_DEFAULT, scratch_pool));

  err = svn_client_add5(local_abspath, svn_depth_empty, FALSE, FALSE, FALSE,
                        make_parents, ctx, scratch_pool);

  /* If we created a new directory, but couldn't add it to version
     control, then delete it. */
  if (err && (orig_kind == svn_node_none))
    {
      err = svn_error_compose_create(err,
                                     svn_io_remove_dir2(local_abspath, FALSE,
                                                        NULL, NULL,
                                                        scratch_pool));
    }

  return svn_error_trace(err);
}