#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  close_file; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  add_file; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  open_root; int /*<<< orphan*/  set_target_revision; } ;
typedef  TYPE_1__ svn_delta_editor_t ;
struct TYPE_9__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
struct edit_baton {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
 int /*<<< orphan*/  change_dir_prop ; 
 int /*<<< orphan*/  change_file_prop ; 
 int /*<<< orphan*/  close_file ; 
 int /*<<< orphan*/  open_root ; 
 int /*<<< orphan*/  set_target_revision ; 
 TYPE_1__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta_get_cancellation_editor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,struct edit_baton*,TYPE_1__ const**,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_editor_ev1(const svn_delta_editor_t **export_editor,
               void **edit_baton,
               struct edit_baton *eb,
               svn_client_ctx_t *ctx,
               apr_pool_t *result_pool,
               apr_pool_t *scratch_pool)
{
  svn_delta_editor_t *editor = svn_delta_default_editor(result_pool);

  editor->set_target_revision = set_target_revision;
  editor->open_root = open_root;
  editor->add_directory = add_directory;
  editor->add_file = add_file;
  editor->apply_textdelta = apply_textdelta;
  editor->close_file = close_file;
  editor->change_file_prop = change_file_prop;
  editor->change_dir_prop = change_dir_prop;

  SVN_ERR(svn_delta_get_cancellation_editor(ctx->cancel_func,
                                            ctx->cancel_baton,
                                            editor,
                                            eb,
                                            export_editor,
                                            edit_baton,
                                            result_pool));

  return SVN_NO_ERROR;
}