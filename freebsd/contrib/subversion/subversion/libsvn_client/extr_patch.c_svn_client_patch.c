#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_patch_func_t ;
struct TYPE_4__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__CALL_WITH_WRITE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apply_patches (char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 scalar_t__ svn_path_is_url (char const*) ; 

svn_error_t *
svn_client_patch(const char *patch_abspath,
                 const char *wc_dir_abspath,
                 svn_boolean_t dry_run,
                 int strip_count,
                 svn_boolean_t reverse,
                 svn_boolean_t ignore_whitespace,
                 svn_boolean_t remove_tempfiles,
                 svn_client_patch_func_t patch_func,
                 void *patch_baton,
                 svn_client_ctx_t *ctx,
                 apr_pool_t *scratch_pool)
{
  svn_node_kind_t kind;

  if (strip_count < 0)
    return svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL,
                            _("strip count must be positive"));

  if (svn_path_is_url(wc_dir_abspath))
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("'%s' is not a local path"),
                             svn_dirent_local_style(wc_dir_abspath,
                                                    scratch_pool));

  SVN_ERR(svn_io_check_path(patch_abspath, &kind, scratch_pool));
  if (kind == svn_node_none)
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("'%s' does not exist"),
                             svn_dirent_local_style(patch_abspath,
                                                    scratch_pool));
  if (kind != svn_node_file)
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("'%s' is not a file"),
                             svn_dirent_local_style(patch_abspath,
                                                    scratch_pool));

  SVN_ERR(svn_io_check_path(wc_dir_abspath, &kind, scratch_pool));
  if (kind == svn_node_none)
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("'%s' does not exist"),
                             svn_dirent_local_style(wc_dir_abspath,
                                                    scratch_pool));
  if (kind != svn_node_dir)
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("'%s' is not a directory"),
                             svn_dirent_local_style(wc_dir_abspath,
                                                    scratch_pool));

  SVN_WC__CALL_WITH_WRITE_LOCK(
    apply_patches(patch_abspath, wc_dir_abspath, dry_run, strip_count,
                  reverse, ignore_whitespace, remove_tempfiles,
                  patch_func, patch_baton, ctx, scratch_pool),
    ctx->wc_ctx, wc_dir_abspath, FALSE /* lock_anchor */, scratch_pool);
  return SVN_NO_ERROR;
}