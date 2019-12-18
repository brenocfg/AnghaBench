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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {struct dump_edit_baton* fetch_baton; int /*<<< orphan*/  fetch_kind_func; int /*<<< orphan*/  fetch_props_func; int /*<<< orphan*/  fetch_base_func; } ;
typedef  TYPE_1__ svn_delta_shim_callbacks_t ;
struct TYPE_12__ {int /*<<< orphan*/  close_edit; int /*<<< orphan*/  close_file; int /*<<< orphan*/  open_file; int /*<<< orphan*/  add_file; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  close_directory; int /*<<< orphan*/  open_directory; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  delete_entry; int /*<<< orphan*/  open_root; } ;
typedef  TYPE_2__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
struct dump_edit_baton {char const* update_anchor_relpath; int /*<<< orphan*/  delta_abspath; int /*<<< orphan*/  delta_file; int /*<<< orphan*/  pool; int /*<<< orphan*/ * pending_db; int /*<<< orphan*/  current_revision; int /*<<< orphan*/ * ra_session; int /*<<< orphan*/ * stream; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
 struct dump_edit_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
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
 TYPE_2__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta_get_cancellation_editor (int /*<<< orphan*/ ,void*,TYPE_2__*,struct dump_edit_baton*,TYPE_2__ const**,void**,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_delta_shim_callbacks_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_editor__insert_shims (TYPE_2__ const**,void**,TYPE_2__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_on_close ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_rdump__get_dump_editor(const svn_delta_editor_t **editor,
                           void **edit_baton,
                           svn_revnum_t revision,
                           svn_stream_t *stream,
                           svn_ra_session_t *ra_session,
                           const char *update_anchor_relpath,
                           svn_cancel_func_t cancel_func,
                           void *cancel_baton,
                           apr_pool_t *pool)
{
  struct dump_edit_baton *eb;
  svn_delta_editor_t *de;
  svn_delta_shim_callbacks_t *shim_callbacks =
                                        svn_delta_shim_callbacks_default(pool);

  eb = apr_pcalloc(pool, sizeof(struct dump_edit_baton));
  eb->stream = stream;
  eb->ra_session = ra_session;
  eb->update_anchor_relpath = update_anchor_relpath;
  eb->current_revision = revision;
  eb->pending_db = NULL;

  /* Create a special per-revision pool */
  eb->pool = svn_pool_create(pool);

  /* Open a unique temporary file for all textdelta applications in
     this edit session. The file is automatically closed and cleaned
     up when the edit session is done. */
  SVN_ERR(svn_io_open_unique_file3(&(eb->delta_file), &(eb->delta_abspath),
                                   NULL, svn_io_file_del_on_close, pool, pool));

  de = svn_delta_default_editor(pool);
  de->open_root = open_root;
  de->delete_entry = delete_entry;
  de->add_directory = add_directory;
  de->open_directory = open_directory;
  de->close_directory = close_directory;
  de->change_dir_prop = change_dir_prop;
  de->change_file_prop = change_file_prop;
  de->apply_textdelta = apply_textdelta;
  de->add_file = add_file;
  de->open_file = open_file;
  de->close_file = close_file;
  de->close_edit = close_edit;

  /* Set the edit_baton and editor. */
  *edit_baton = eb;
  *editor = de;

  /* Wrap this editor in a cancellation editor. */
  SVN_ERR(svn_delta_get_cancellation_editor(cancel_func, cancel_baton,
                                            de, eb, editor, edit_baton, pool));

  shim_callbacks->fetch_base_func = fetch_base_func;
  shim_callbacks->fetch_props_func = fetch_props_func;
  shim_callbacks->fetch_kind_func = fetch_kind_func;
  shim_callbacks->fetch_baton = eb;

  SVN_ERR(svn_editor__insert_shims(editor, edit_baton, *editor, *edit_baton,
                                   NULL, NULL, shim_callbacks, pool, pool));

  return SVN_NO_ERROR;
}