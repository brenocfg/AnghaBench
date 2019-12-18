#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ node_status; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
struct TYPE_19__ {int kind; } ;
typedef  TYPE_2__ svn_wc_notify_t ;
typedef  int svn_node_kind_t ;
struct TYPE_20__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
struct cleanup_status_walk_baton {TYPE_12__* ctx; int /*<<< orphan*/  remove_unversioned_items; int /*<<< orphan*/  remove_ignored_items; int /*<<< orphan*/  vacuum_pristines; int /*<<< orphan*/  clear_dav_cache; int /*<<< orphan*/  fix_timestamps; int /*<<< orphan*/  break_locks; scalar_t__ include_externals; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_17__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_3__*) ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* do_cleanup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_io_check_path (char const*,int*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  svn_node_dir 131 
#define  svn_node_file 130 
#define  svn_node_none 129 
#define  svn_node_symlink 128 
 TYPE_2__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_cleanup_external ; 
 int /*<<< orphan*/  svn_wc_notify_delete ; 
 scalar_t__ svn_wc_status_external ; 
 scalar_t__ svn_wc_status_ignored ; 
 scalar_t__ svn_wc_status_unversioned ; 

__attribute__((used)) static svn_error_t *
cleanup_status_walk(void *baton,
                    const char *local_abspath,
                    const svn_wc_status3_t *status,
                    apr_pool_t *scratch_pool)
{
  struct cleanup_status_walk_baton *b = baton;
  svn_node_kind_t kind_on_disk;
  svn_wc_notify_t *notify;

  if (status->node_status == svn_wc_status_external && b->include_externals)
    {
      svn_error_t *err;

      SVN_ERR(svn_io_check_path(local_abspath, &kind_on_disk, scratch_pool));
      if (kind_on_disk == svn_node_dir)
        {
          if (b->ctx->notify_func2)
            {
              notify = svn_wc_create_notify(local_abspath,
                                            svn_wc_notify_cleanup_external,
                                            scratch_pool);
              b->ctx->notify_func2(b->ctx->notify_baton2, notify,
                                   scratch_pool);
            }

          err = do_cleanup(local_abspath,
                           b->break_locks,
                           b->fix_timestamps,
                           b->clear_dav_cache,
                           b->vacuum_pristines,
                           b->remove_unversioned_items,
                           b->remove_ignored_items,
                           TRUE /* include_externals */,
                           b->ctx, scratch_pool);
          if (err && err->apr_err == SVN_ERR_WC_NOT_WORKING_COPY)
            {
              svn_error_clear(err);
              return SVN_NO_ERROR;
            }
          else
            SVN_ERR(err);
        }

      return SVN_NO_ERROR;
    }

  if (status->node_status == svn_wc_status_ignored)
    {
      if (!b->remove_ignored_items)
        return SVN_NO_ERROR;
    }
  else if (status->node_status == svn_wc_status_unversioned)
    {
      if (!b->remove_unversioned_items)
        return SVN_NO_ERROR;
    }
  else
    return SVN_NO_ERROR;

  SVN_ERR(svn_io_check_path(local_abspath, &kind_on_disk, scratch_pool));
  switch (kind_on_disk)
    {
      case svn_node_file:
      case svn_node_symlink:
        SVN_ERR(svn_io_remove_file2(local_abspath, FALSE, scratch_pool));
        break;
      case svn_node_dir:
        SVN_ERR(svn_io_remove_dir2(local_abspath, FALSE,
                                   b->ctx->cancel_func, b->ctx->cancel_baton,
                                   scratch_pool));
        break;
      case svn_node_none:
      default:
        return SVN_NO_ERROR;
    }

  if (b->ctx->notify_func2)
    {
      notify = svn_wc_create_notify(local_abspath, svn_wc_notify_delete,
                                    scratch_pool);
      notify->kind = kind_on_disk;
      b->ctx->notify_func2(b->ctx->notify_baton2, notify, scratch_pool);
    }

  return SVN_NO_ERROR;
}