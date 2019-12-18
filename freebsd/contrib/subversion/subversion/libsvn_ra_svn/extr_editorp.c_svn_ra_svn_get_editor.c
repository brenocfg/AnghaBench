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
typedef  int /*<<< orphan*/  svn_ra_svn_edit_callback ;
struct TYPE_10__ {int /*<<< orphan*/  shim_callbacks; } ;
typedef  TYPE_1__ svn_ra_svn_conn_t ;
struct TYPE_11__ {int /*<<< orphan*/  abort_edit; int /*<<< orphan*/  close_edit; int /*<<< orphan*/  absent_file; int /*<<< orphan*/  close_file; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  open_file; int /*<<< orphan*/  add_file; int /*<<< orphan*/  absent_directory; int /*<<< orphan*/  close_directory; int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  open_directory; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  delete_entry; int /*<<< orphan*/  open_root; int /*<<< orphan*/  set_target_revision; } ;
typedef  TYPE_2__ svn_delta_editor_t ;
struct TYPE_12__ {int /*<<< orphan*/  got_status; scalar_t__ next_token; void* callback_baton; int /*<<< orphan*/  callback; TYPE_1__* conn; } ;
typedef  TYPE_3__ ra_svn_edit_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ra_svn_abort_edit ; 
 int /*<<< orphan*/  ra_svn_absent_dir ; 
 int /*<<< orphan*/  ra_svn_absent_file ; 
 int /*<<< orphan*/  ra_svn_add_dir ; 
 int /*<<< orphan*/  ra_svn_add_file ; 
 int /*<<< orphan*/  ra_svn_apply_textdelta ; 
 int /*<<< orphan*/  ra_svn_change_dir_prop ; 
 int /*<<< orphan*/  ra_svn_change_file_prop ; 
 int /*<<< orphan*/  ra_svn_close_dir ; 
 int /*<<< orphan*/  ra_svn_close_edit ; 
 int /*<<< orphan*/  ra_svn_close_file ; 
 int /*<<< orphan*/  ra_svn_delete_entry ; 
 int /*<<< orphan*/  ra_svn_open_dir ; 
 int /*<<< orphan*/  ra_svn_open_file ; 
 int /*<<< orphan*/  ra_svn_open_root ; 
 int /*<<< orphan*/  ra_svn_target_rev ; 
 TYPE_2__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_editor__insert_shims (TYPE_2__ const**,void**,TYPE_2__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 

void svn_ra_svn_get_editor(const svn_delta_editor_t **editor,
                           void **edit_baton, svn_ra_svn_conn_t *conn,
                           apr_pool_t *pool,
                           svn_ra_svn_edit_callback callback,
                           void *callback_baton)
{
  svn_delta_editor_t *ra_svn_editor = svn_delta_default_editor(pool);
  ra_svn_edit_baton_t *eb;

  eb = apr_palloc(pool, sizeof(*eb));
  eb->conn = conn;
  eb->callback = callback;
  eb->callback_baton = callback_baton;
  eb->next_token = 0;
  eb->got_status = FALSE;

  ra_svn_editor->set_target_revision = ra_svn_target_rev;
  ra_svn_editor->open_root = ra_svn_open_root;
  ra_svn_editor->delete_entry = ra_svn_delete_entry;
  ra_svn_editor->add_directory = ra_svn_add_dir;
  ra_svn_editor->open_directory = ra_svn_open_dir;
  ra_svn_editor->change_dir_prop = ra_svn_change_dir_prop;
  ra_svn_editor->close_directory = ra_svn_close_dir;
  ra_svn_editor->absent_directory = ra_svn_absent_dir;
  ra_svn_editor->add_file = ra_svn_add_file;
  ra_svn_editor->open_file = ra_svn_open_file;
  ra_svn_editor->apply_textdelta = ra_svn_apply_textdelta;
  ra_svn_editor->change_file_prop = ra_svn_change_file_prop;
  ra_svn_editor->close_file = ra_svn_close_file;
  ra_svn_editor->absent_file = ra_svn_absent_file;
  ra_svn_editor->close_edit = ra_svn_close_edit;
  ra_svn_editor->abort_edit = ra_svn_abort_edit;

  *editor = ra_svn_editor;
  *edit_baton = eb;

  svn_error_clear(svn_editor__insert_shims(editor, edit_baton, *editor,
                                           *edit_baton, NULL, NULL,
                                           conn->shim_callbacks,
                                           pool, pool));
}