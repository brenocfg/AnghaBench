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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  abort_edit; int /*<<< orphan*/  close_edit; int /*<<< orphan*/  absent_file; int /*<<< orphan*/  close_file; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  open_file; int /*<<< orphan*/  add_file; int /*<<< orphan*/  absent_directory; int /*<<< orphan*/  close_directory; int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  open_directory; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  delete_entry; int /*<<< orphan*/  open_root; int /*<<< orphan*/  set_target_revision; } ;
typedef  TYPE_1__ svn_delta_editor_t ;
struct edit_baton {int /*<<< orphan*/  prefix; scalar_t__ indent_level; int /*<<< orphan*/ * out; void* wrapped_edit_baton; TYPE_1__ const* wrapped_editor; } ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort_edit ; 
 int /*<<< orphan*/  absent_directory ; 
 int /*<<< orphan*/  absent_file ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
 scalar_t__ apr_file_open_stdout (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 void* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrcat (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,char*) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_delta__get_debug_editor(const svn_delta_editor_t **editor,
                            void **edit_baton,
                            const svn_delta_editor_t *wrapped_editor,
                            void *wrapped_edit_baton,
                            const char *prefix,
                            apr_pool_t *pool)
{
  svn_delta_editor_t *tree_editor = apr_palloc(pool, sizeof(*tree_editor));
  struct edit_baton *eb = apr_palloc(pool, sizeof(*eb));
  apr_file_t *errfp;
  svn_stream_t *out;

  apr_status_t apr_err = apr_file_open_stdout(&errfp, pool);
  if (apr_err)
    return svn_error_wrap_apr(apr_err, "Problem opening stderr");

  out = svn_stream_from_aprfile2(errfp, TRUE, pool);

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
  tree_editor->change_file_prop = change_file_prop;
  tree_editor->close_file = close_file;
  tree_editor->absent_file = absent_file;
  tree_editor->close_edit = close_edit;
  tree_editor->abort_edit = abort_edit;

  eb->wrapped_editor = wrapped_editor;
  eb->wrapped_edit_baton = wrapped_edit_baton;
  eb->out = out;
  eb->indent_level = 0;
  /* This is DBG_FLAG from ../libsvn_subr/debug.c */
  eb->prefix = apr_pstrcat(pool, "DBG: ", prefix, SVN_VA_NULL);

  *editor = tree_editor;
  *edit_baton = eb;

  return SVN_NO_ERROR;
}