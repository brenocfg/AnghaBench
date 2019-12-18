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
typedef  int /*<<< orphan*/  svn_wc_notify_t ;
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  crop_children (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_base_remove (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_switched (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  svn_wc__db_status_added 134 
#define  svn_wc__db_status_deleted 133 
#define  svn_wc__db_status_excluded 132 
#define  svn_wc__db_status_incomplete 131 
#define  svn_wc__db_status_normal 130 
#define  svn_wc__db_status_not_present 129 
#define  svn_wc__db_status_server_excluded 128 
 int /*<<< orphan*/  svn_wc__node_has_local_mods (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_exclude ; 

svn_error_t *
svn_wc_exclude(svn_wc_context_t *wc_ctx,
               const char *local_abspath,
               svn_cancel_func_t cancel_func,
               void *cancel_baton,
               svn_wc_notify_func2_t notify_func,
               void *notify_baton,
               apr_pool_t *scratch_pool)
{
  svn_boolean_t is_root, is_switched;
  svn_wc__db_status_t status;
  svn_node_kind_t kind;
  svn_revnum_t revision;
  svn_depth_t depth;
  svn_boolean_t modified, all_deletes;
  const char *repos_relpath, *repos_root, *repos_uuid;

  SVN_ERR(svn_wc__db_is_switched(&is_root, &is_switched, NULL,
                                 wc_ctx->db, local_abspath, scratch_pool));

  if (is_root)
    {
       return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                _("Cannot exclude '%s': "
                                  "it is a working copy root"),
                                svn_dirent_local_style(local_abspath,
                                                       scratch_pool));
    }
  if (is_switched)
    {
      return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                               _("Cannot exclude '%s': "
                                 "it is a switched path"),
                               svn_dirent_local_style(local_abspath,
                                                      scratch_pool));
    }

  SVN_ERR(svn_wc__db_read_info(&status, &kind, &revision, &repos_relpath,
                               &repos_root, &repos_uuid, NULL, NULL, NULL,
                               &depth, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL,
                               wc_ctx->db, local_abspath,
                               scratch_pool, scratch_pool));

  switch (status)
    {
      case svn_wc__db_status_server_excluded:
      case svn_wc__db_status_excluded:
      case svn_wc__db_status_not_present:
        return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                                 _("The node '%s' was not found."),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool));

      case svn_wc__db_status_added:
        /* Would have to check parents if we want to allow this */
        return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                 _("Cannot exclude '%s': it is to be added "
                                   "to the repository. Try commit instead"),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool));
      case svn_wc__db_status_deleted:
        /* Would have to check parents if we want to allow this */
        return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                 _("Cannot exclude '%s': it is to be deleted "
                                   "from the repository. Try commit instead"),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool));

      case svn_wc__db_status_normal:
      case svn_wc__db_status_incomplete:
      default:
        break; /* Ok to exclude */
    }

  SVN_ERR(svn_wc__node_has_local_mods(&modified, &all_deletes,
                                      wc_ctx->db, local_abspath, FALSE,
                                      cancel_func, cancel_baton,
                                      scratch_pool));

  if (!modified || all_deletes)
    {
      /* Remove all working copy data below local_abspath */
      SVN_ERR(svn_wc__db_base_remove(wc_ctx->db, local_abspath,
                                     FALSE /* keep_working */,
                                     FALSE, TRUE,
                                     revision,
                                     NULL, NULL,
                                     scratch_pool));

      SVN_ERR(svn_wc__wq_run(wc_ctx->db, local_abspath,
                             cancel_func, cancel_baton,
                             scratch_pool));

      if (notify_func)
        {
          svn_wc_notify_t *notify;
          notify = svn_wc_create_notify(local_abspath,
                                        svn_wc_notify_exclude,
                                        scratch_pool);
          notify_func(notify_baton, notify, scratch_pool);
        }
    }
  else
    {
      /* Do the next best thing: retry below this path */
      SVN_ERR(crop_children(wc_ctx->db, local_abspath, depth, svn_depth_empty,
                            notify_func, notify_baton,
                            cancel_func, cancel_baton,
                            scratch_pool));
    }

  return SVN_NO_ERROR;
}