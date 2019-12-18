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
typedef  scalar_t__ svn_depth_t ;
struct TYPE_5__ {int /*<<< orphan*/  close_edit; int /*<<< orphan*/  absent_file; int /*<<< orphan*/  close_file; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  open_file; int /*<<< orphan*/  add_file; int /*<<< orphan*/  absent_directory; int /*<<< orphan*/  close_directory; int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  open_directory; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  delete_entry; int /*<<< orphan*/  open_root; int /*<<< orphan*/  set_target_revision; } ;
typedef  TYPE_1__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct edit_baton {scalar_t__ requested_depth; int /*<<< orphan*/  has_target; void* wrapped_edit_baton; TYPE_1__ const* wrapped_editor; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  absent_directory ; 
 int /*<<< orphan*/  absent_file ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
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
 scalar_t__ svn_depth_infinity ; 
 scalar_t__ svn_depth_unknown ; 

svn_error_t *
svn_delta_depth_filter_editor(const svn_delta_editor_t **editor,
                              void **edit_baton,
                              const svn_delta_editor_t *wrapped_editor,
                              void *wrapped_edit_baton,
                              svn_depth_t requested_depth,
                              svn_boolean_t has_target,
                              apr_pool_t *pool)
{
  svn_delta_editor_t *depth_filter_editor;
  struct edit_baton *eb;

  /* Easy out: if the caller wants infinite depth, there's nothing to
     filter, so just return the editor we were supposed to wrap.  And
     if they've asked for an unknown depth, we can't possibly know
     what that means, so why bother?  */
  if ((requested_depth == svn_depth_unknown)
      || (requested_depth == svn_depth_infinity))
    {
      *editor = wrapped_editor;
      *edit_baton = wrapped_edit_baton;
      return SVN_NO_ERROR;
    }

  depth_filter_editor = svn_delta_default_editor(pool);
  depth_filter_editor->set_target_revision = set_target_revision;
  depth_filter_editor->open_root = open_root;
  depth_filter_editor->delete_entry = delete_entry;
  depth_filter_editor->add_directory = add_directory;
  depth_filter_editor->open_directory = open_directory;
  depth_filter_editor->change_dir_prop = change_dir_prop;
  depth_filter_editor->close_directory = close_directory;
  depth_filter_editor->absent_directory = absent_directory;
  depth_filter_editor->add_file = add_file;
  depth_filter_editor->open_file = open_file;
  depth_filter_editor->apply_textdelta = apply_textdelta;
  depth_filter_editor->change_file_prop = change_file_prop;
  depth_filter_editor->close_file = close_file;
  depth_filter_editor->absent_file = absent_file;
  depth_filter_editor->close_edit = close_edit;

  eb = apr_palloc(pool, sizeof(*eb));
  eb->wrapped_editor = wrapped_editor;
  eb->wrapped_edit_baton = wrapped_edit_baton;
  eb->has_target = has_target;
  eb->requested_depth = requested_depth;

  *editor = depth_filter_editor;
  *edit_baton = eb;

  return SVN_NO_ERROR;
}