#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* finish_report ) (void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_path ) (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_11__ {int /*<<< orphan*/  close_file; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  add_file; int /*<<< orphan*/  close_directory; int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  close_edit; int /*<<< orphan*/  open_root; } ;
typedef  TYPE_2__ svn_delta_editor_t ;
struct TYPE_12__ {int /*<<< orphan*/  rev; } ;
typedef  TYPE_3__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
struct edit_baton_t {char const* anchor_abspath; void* notify_baton; int /*<<< orphan*/  notify_func; int /*<<< orphan*/ * wc_ctx; int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dir_add ; 
 int /*<<< orphan*/  dir_change_prop ; 
 int /*<<< orphan*/  dir_close ; 
 int /*<<< orphan*/  edit_close ; 
 int /*<<< orphan*/  edit_open ; 
 int /*<<< orphan*/  file_add ; 
 int /*<<< orphan*/  file_change_prop ; 
 int /*<<< orphan*/  file_close ; 
 int /*<<< orphan*/  file_textdelta ; 
 int /*<<< orphan*/  stub1 (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta_get_cancellation_editor (int /*<<< orphan*/ ,void*,TYPE_2__*,struct edit_baton_t*,TYPE_2__ const**,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_ra_do_update3 (int /*<<< orphan*/ *,TYPE_1__ const**,void**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
copy_foreign_dir(svn_ra_session_t *ra_session,
                 svn_client__pathrev_t *location,
                 svn_wc_context_t *wc_ctx,
                 const char *dst_abspath,
                 svn_depth_t depth,
                 svn_wc_notify_func2_t notify_func,
                 void *notify_baton,
                 svn_cancel_func_t cancel_func,
                 void *cancel_baton,
                 apr_pool_t *scratch_pool)
{
  struct edit_baton_t eb;
  svn_delta_editor_t *editor = svn_delta_default_editor(scratch_pool);
  const svn_delta_editor_t *wrapped_editor;
  void *wrapped_baton;
  const svn_ra_reporter3_t *reporter;
  void *reporter_baton;

  eb.pool = scratch_pool;
  eb.anchor_abspath = dst_abspath;

  eb.wc_ctx = wc_ctx;
  eb.notify_func = notify_func;
  eb.notify_baton  = notify_baton;

  editor->open_root = edit_open;
  editor->close_edit = edit_close;

  editor->add_directory = dir_add;
  editor->change_dir_prop = dir_change_prop;
  editor->close_directory = dir_close;

  editor->add_file = file_add;
  editor->change_file_prop = file_change_prop;
  editor->apply_textdelta = file_textdelta;
  editor->close_file = file_close;

  SVN_ERR(svn_delta_get_cancellation_editor(cancel_func, cancel_baton,
                                            editor, &eb,
                                            &wrapped_editor, &wrapped_baton,
                                            scratch_pool));

  SVN_ERR(svn_ra_do_update3(ra_session, &reporter, &reporter_baton,
                            location->rev, "", svn_depth_infinity,
                            FALSE, FALSE, wrapped_editor, wrapped_baton,
                            scratch_pool, scratch_pool));

  SVN_ERR(reporter->set_path(reporter_baton, "", location->rev, depth,
                             TRUE /* incomplete */,
                             NULL, scratch_pool));

  SVN_ERR(reporter->finish_report(reporter_baton, scratch_pool));

  return SVN_NO_ERROR;
}