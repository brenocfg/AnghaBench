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
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
struct TYPE_3__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int svn_wc__db_status_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  crop_children (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_wc__db_read_info (int*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  svn_wc__db_status_added 134 
#define  svn_wc__db_status_deleted 133 
#define  svn_wc__db_status_excluded 132 
#define  svn_wc__db_status_incomplete 131 
#define  svn_wc__db_status_normal 130 
#define  svn_wc__db_status_not_present 129 
#define  svn_wc__db_status_server_excluded 128 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_crop_tree2(svn_wc_context_t *wc_ctx,
                  const char *local_abspath,
                  svn_depth_t depth,
                  svn_cancel_func_t cancel_func,
                  void *cancel_baton,
                  svn_wc_notify_func2_t notify_func,
                  void *notify_baton,
                  apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db = wc_ctx->db;
  svn_wc__db_status_t status;
  svn_node_kind_t kind;
  svn_depth_t dir_depth;

  /* Only makes sense when the depth is restrictive. */
  if (depth == svn_depth_infinity)
    return SVN_NO_ERROR; /* Nothing to crop */
  if (!(depth >= svn_depth_empty && depth < svn_depth_infinity))
    return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
      _("Can only crop a working copy with a restrictive depth"));

  SVN_ERR(svn_wc__db_read_info(&status, &kind, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, &dir_depth, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL,
                               db, local_abspath,
                               scratch_pool, scratch_pool));

  if (kind != svn_node_dir)
    return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
      _("Can only crop directories"));

  switch (status)
    {
      case svn_wc__db_status_not_present:
      case svn_wc__db_status_server_excluded:
        return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                                 _("The node '%s' was not found."),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool));

      case svn_wc__db_status_deleted:
        return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                               _("Cannot crop '%s': it is going to be removed "
                                 "from repository. Try commit instead"),
                               svn_dirent_local_style(local_abspath,
                                                      scratch_pool));

      case svn_wc__db_status_added:
        return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                 _("Cannot crop '%s': it is to be added "
                                   "to the repository. Try commit instead"),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool));
      case svn_wc__db_status_excluded:
        return SVN_NO_ERROR; /* Nothing to do */

      case svn_wc__db_status_normal:
      case svn_wc__db_status_incomplete:
        break;

      default:
        SVN_ERR_MALFUNCTION();
    }

  SVN_ERR(crop_children(db, local_abspath, dir_depth, depth,
                        notify_func, notify_baton,
                        cancel_func, cancel_baton, scratch_pool));

  return svn_error_trace(svn_wc__wq_run(db, local_abspath,
                                        cancel_func, cancel_baton,
                                        scratch_pool));
}