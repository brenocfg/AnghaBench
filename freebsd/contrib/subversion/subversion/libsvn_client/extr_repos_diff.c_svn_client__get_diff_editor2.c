#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_diff_tree_processor_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_11__ {struct edit_baton* fetch_baton; int /*<<< orphan*/  fetch_base_func; int /*<<< orphan*/  fetch_props_func; int /*<<< orphan*/  fetch_kind_func; } ;
typedef  TYPE_1__ svn_delta_shim_callbacks_t ;
struct TYPE_12__ {int /*<<< orphan*/  absent_file; int /*<<< orphan*/  absent_directory; int /*<<< orphan*/  close_edit; int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  close_directory; int /*<<< orphan*/  close_file; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  open_file; int /*<<< orphan*/  add_file; int /*<<< orphan*/  open_directory; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  delete_entry; int /*<<< orphan*/  open_root; int /*<<< orphan*/  set_target_revision; } ;
typedef  TYPE_2__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct edit_baton {int /*<<< orphan*/ * pool; void* cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  text_deltas; int /*<<< orphan*/  empty_hash; int /*<<< orphan*/ * empty_file; int /*<<< orphan*/  target_revision; int /*<<< orphan*/  revision; int /*<<< orphan*/ * ra_session; int /*<<< orphan*/  const* processor; int /*<<< orphan*/  depth; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  absent_directory ; 
 int /*<<< orphan*/  absent_file ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 struct edit_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  change_dir_prop ; 
 int /*<<< orphan*/  change_file_prop ; 
 int /*<<< orphan*/  close_directory ; 
 int /*<<< orphan*/  close_edit ; 
 int /*<<< orphan*/  close_file ; 
 int /*<<< orphan*/  delete_entry ; 
 int /*<<< orphan*/  fetch_base_func ; 
 int /*<<< orphan*/  fetch_kind_func ; 
 int /*<<< orphan*/  fetch_props_func ; 
 int /*<<< orphan*/  open_directory ; 
 int /*<<< orphan*/  open_file ; 
 int /*<<< orphan*/  open_root ; 
 int /*<<< orphan*/  set_target_revision ; 
 TYPE_2__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta_get_cancellation_editor (int /*<<< orphan*/ ,void*,TYPE_2__*,struct edit_baton*,TYPE_2__ const**,void**,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_delta_shim_callbacks_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_editor__insert_shims (TYPE_2__ const**,void**,TYPE_2__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__get_diff_editor2(const svn_delta_editor_t **editor,
                             void **edit_baton,
                             svn_ra_session_t *ra_session,
                             svn_depth_t depth,
                             svn_revnum_t revision,
                             svn_boolean_t text_deltas,
                             const svn_diff_tree_processor_t *processor,
                             svn_cancel_func_t cancel_func,
                             void *cancel_baton,
                             apr_pool_t *result_pool)
{
  apr_pool_t *editor_pool = svn_pool_create(result_pool);
  svn_delta_editor_t *tree_editor = svn_delta_default_editor(editor_pool);
  struct edit_baton *eb = apr_pcalloc(editor_pool, sizeof(*eb));
  svn_delta_shim_callbacks_t *shim_callbacks =
                                svn_delta_shim_callbacks_default(editor_pool);

  eb->pool = editor_pool;
  eb->depth = depth;

  eb->processor = processor;

  eb->ra_session = ra_session;

  eb->revision = revision;
  eb->target_revision = SVN_INVALID_REVNUM;
  eb->empty_file = NULL;
  eb->empty_hash = apr_hash_make(eb->pool);
  eb->text_deltas = text_deltas;
  eb->cancel_func = cancel_func;
  eb->cancel_baton = cancel_baton;

  tree_editor->set_target_revision = set_target_revision;
  tree_editor->open_root = open_root;
  tree_editor->delete_entry = delete_entry;
  tree_editor->add_directory = add_directory;
  tree_editor->open_directory = open_directory;
  tree_editor->add_file = add_file;
  tree_editor->open_file = open_file;
  tree_editor->apply_textdelta = apply_textdelta;
  tree_editor->close_file = close_file;
  tree_editor->close_directory = close_directory;
  tree_editor->change_file_prop = change_file_prop;
  tree_editor->change_dir_prop = change_dir_prop;
  tree_editor->close_edit = close_edit;
  tree_editor->absent_directory = absent_directory;
  tree_editor->absent_file = absent_file;

  SVN_ERR(svn_delta_get_cancellation_editor(cancel_func, cancel_baton,
                                            tree_editor, eb,
                                            editor, edit_baton,
                                            eb->pool));

  shim_callbacks->fetch_kind_func = fetch_kind_func;
  shim_callbacks->fetch_props_func = fetch_props_func;
  shim_callbacks->fetch_base_func = fetch_base_func;
  shim_callbacks->fetch_baton = eb;

  SVN_ERR(svn_editor__insert_shims(editor, edit_baton, *editor, *edit_baton,
                                   NULL, NULL, shim_callbacks,
                                   result_pool, result_pool));

  return SVN_NO_ERROR;
}