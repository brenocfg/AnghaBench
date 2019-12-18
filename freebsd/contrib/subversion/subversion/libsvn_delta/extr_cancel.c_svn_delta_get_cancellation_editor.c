#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  abort_edit; int /*<<< orphan*/  close_edit; int /*<<< orphan*/  absent_file; int /*<<< orphan*/  close_file; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  apply_textdelta_stream; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  open_file; int /*<<< orphan*/  add_file; int /*<<< orphan*/  absent_directory; int /*<<< orphan*/  close_directory; int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  open_directory; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  delete_entry; int /*<<< orphan*/  open_root; int /*<<< orphan*/  set_target_revision; } ;
typedef  TYPE_1__ svn_delta_editor_t ;
typedef  scalar_t__ svn_cancel_func_t ;
struct edit_baton {void* cancel_baton; scalar_t__ cancel_func; void* wrapped_edit_baton; TYPE_1__ const* wrapped_editor; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  abort_edit ; 
 int /*<<< orphan*/  absent_directory ; 
 int /*<<< orphan*/  absent_file ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
 int /*<<< orphan*/  apply_textdelta_stream ; 
 struct edit_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  change_dir_prop ; 
 int /*<<< orphan*/  change_file_prop ; 
 int /*<<< orphan*/  close_directory ; 
 int /*<<< orphan*/  close_edit ; 
 int /*<<< orphan*/  close_file ; 
 int /*<<< orphan*/  delete_entry ; 
 int /*<<< orphan*/  open_directory ; 
 int /*<<< orphan*/  open_file ; 
 int /*<<< orphan*/  open_root ; 
 int /*<<< orphan*/  set_target_revision ; 
 TYPE_1__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_delta_get_cancellation_editor(svn_cancel_func_t cancel_func,
                                  void *cancel_baton,
                                  const svn_delta_editor_t *wrapped_editor,
                                  void *wrapped_edit_baton,
                                  const svn_delta_editor_t **editor,
                                  void **edit_baton,
                                  apr_pool_t *pool)
{
  if (cancel_func)
    {
      svn_delta_editor_t *tree_editor = svn_delta_default_editor(pool);
      struct edit_baton *eb = apr_palloc(pool, sizeof(*eb));

      tree_editor->set_target_revision = set_target_revision;
      tree_editor->open_root = open_root;
      tree_editor->delete_entry = delete_entry;
      tree_editor->add_directory = add_directory;
      tree_editor->open_directory = open_directory;
      tree_editor->change_dir_prop = change_dir_prop;
      tree_editor->close_directory = close_directory;
      tree_editor->absent_directory = absent_directory;
      tree_editor->add_file = add_file;
      tree_editor->open_file = open_file;
      tree_editor->apply_textdelta = apply_textdelta;
      tree_editor->apply_textdelta_stream = apply_textdelta_stream;
      tree_editor->change_file_prop = change_file_prop;
      tree_editor->close_file = close_file;
      tree_editor->absent_file = absent_file;
      tree_editor->close_edit = close_edit;
      tree_editor->abort_edit = abort_edit;

      eb->wrapped_editor = wrapped_editor;
      eb->wrapped_edit_baton = wrapped_edit_baton;
      eb->cancel_func = cancel_func;
      eb->cancel_baton = cancel_baton;

      *editor = tree_editor;
      *edit_baton = eb;
    }
  else
    {
      *editor = wrapped_editor;
      *edit_baton = wrapped_edit_baton;
    }

  return SVN_NO_ERROR;
}