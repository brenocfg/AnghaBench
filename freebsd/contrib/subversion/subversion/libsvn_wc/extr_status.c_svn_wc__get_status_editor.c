#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_status_func4_t ;
struct TYPE_17__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_18__ {struct svn_wc__shim_fetch_baton_t* fetch_baton; int /*<<< orphan*/  fetch_base_func; int /*<<< orphan*/  fetch_props_func; int /*<<< orphan*/  fetch_kind_func; } ;
typedef  TYPE_3__ svn_delta_shim_callbacks_t ;
struct TYPE_19__ {int /*<<< orphan*/  close_edit; int /*<<< orphan*/  close_file; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  open_file; int /*<<< orphan*/  add_file; int /*<<< orphan*/  close_directory; int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  open_directory; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  delete_entry; int /*<<< orphan*/  open_root; int /*<<< orphan*/  set_target_revision; } ;
typedef  TYPE_4__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  void* svn_boolean_t ;
struct svn_wc__shim_fetch_baton_t {void* fetch_base; void* base_abspath; int /*<<< orphan*/  db; } ;
struct TYPE_16__ {int ignore_text_mods; int /*<<< orphan*/  externals; int /*<<< orphan*/ * repos_root; int /*<<< orphan*/ * repos_locks; void* check_working_copy; int /*<<< orphan*/  target_abspath; int /*<<< orphan*/  db; } ;
struct edit_baton {void* anchor_abspath; int /*<<< orphan*/  anchor_status; int /*<<< orphan*/  const* ignores; int /*<<< orphan*/  target_abspath; TYPE_1__ wb; void* root_opened; void* target_basename; void* cancel_baton; int /*<<< orphan*/  cancel_func; void* status_baton; int /*<<< orphan*/  status_func; void* no_ignore; void* get_all; int /*<<< orphan*/  db; int /*<<< orphan*/ * target_revision; int /*<<< orphan*/  default_depth; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  const apr_array_header_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
 struct svn_wc__shim_fetch_baton_t* apr_palloc (int /*<<< orphan*/ *,int) ; 
 struct edit_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  change_dir_prop ; 
 int /*<<< orphan*/  change_file_prop ; 
 int /*<<< orphan*/  close_directory ; 
 int /*<<< orphan*/  close_edit ; 
 int /*<<< orphan*/  close_file ; 
 int /*<<< orphan*/  delete_entry ; 
 int /*<<< orphan*/  internal_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_directory ; 
 int /*<<< orphan*/  open_file ; 
 int /*<<< orphan*/  open_root ; 
 int /*<<< orphan*/  set_target_revision ; 
 TYPE_4__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_delta_get_cancellation_editor (int /*<<< orphan*/ ,void*,TYPE_4__ const*,void*,TYPE_4__ const**,void**,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_delta_shim_callbacks_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_editor__insert_shims (TYPE_4__ const**,void**,TYPE_4__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__ambient_depth_filter_editor (TYPE_4__ const**,void**,int /*<<< orphan*/ ,char const*,char const*,TYPE_4__ const*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_externals_defined_below (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__fetch_base_func ; 
 int /*<<< orphan*/  svn_wc__fetch_kind_func ; 
 int /*<<< orphan*/  svn_wc__fetch_props_func ; 
 int /*<<< orphan*/  svn_wc_get_default_ignores (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__get_status_editor(const svn_delta_editor_t **editor,
                          void **edit_baton,
                          void **set_locks_baton,
                          svn_revnum_t *edit_revision,
                          svn_wc_context_t *wc_ctx,
                          const char *anchor_abspath,
                          const char *target_basename,
                          svn_depth_t depth,
                          svn_boolean_t get_all,
                          svn_boolean_t check_working_copy,
                          svn_boolean_t no_ignore,
                          svn_boolean_t depth_as_sticky,
                          svn_boolean_t server_performs_filtering,
                          const apr_array_header_t *ignore_patterns,
                          svn_wc_status_func4_t status_func,
                          void *status_baton,
                          svn_cancel_func_t cancel_func,
                          void *cancel_baton,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  struct edit_baton *eb;
  svn_delta_editor_t *tree_editor = svn_delta_default_editor(result_pool);
  void *inner_baton;
  struct svn_wc__shim_fetch_baton_t *sfb;
  const svn_delta_editor_t *inner_editor;
  svn_delta_shim_callbacks_t *shim_callbacks =
                                svn_delta_shim_callbacks_default(result_pool);

  /* Construct an edit baton. */
  eb = apr_pcalloc(result_pool, sizeof(*eb));
  eb->default_depth     = depth;
  eb->target_revision   = edit_revision;
  eb->db                = wc_ctx->db;
  eb->get_all           = get_all;
  eb->no_ignore         = no_ignore;
  eb->status_func       = status_func;
  eb->status_baton      = status_baton;
  eb->cancel_func       = cancel_func;
  eb->cancel_baton      = cancel_baton;
  eb->anchor_abspath    = apr_pstrdup(result_pool, anchor_abspath);
  eb->target_abspath    = svn_dirent_join(anchor_abspath, target_basename,
                                          result_pool);

  eb->target_basename   = apr_pstrdup(result_pool, target_basename);
  eb->root_opened       = FALSE;

  eb->wb.db               = wc_ctx->db;
  eb->wb.target_abspath   = eb->target_abspath;
  eb->wb.ignore_text_mods = !check_working_copy;
  eb->wb.check_working_copy = check_working_copy;
  eb->wb.repos_locks      = NULL;
  eb->wb.repos_root       = NULL;

  SVN_ERR(svn_wc__db_externals_defined_below(&eb->wb.externals,
                                             wc_ctx->db, eb->target_abspath,
                                             result_pool, scratch_pool));

  /* Use the caller-provided ignore patterns if provided; the build-time
     configured defaults otherwise. */
  if (ignore_patterns)
    {
      eb->ignores = ignore_patterns;
    }
  else
    {
      apr_array_header_t *ignores;

      SVN_ERR(svn_wc_get_default_ignores(&ignores, NULL, result_pool));
      eb->ignores = ignores;
    }

  /* The edit baton's status structure maps to PATH, and the editor
     have to be aware of whether that is the anchor or the target. */
  SVN_ERR(internal_status(&(eb->anchor_status), wc_ctx->db, anchor_abspath,
                          check_working_copy, result_pool, scratch_pool));

  /* Construct an editor. */
  tree_editor->set_target_revision = set_target_revision;
  tree_editor->open_root = open_root;
  tree_editor->delete_entry = delete_entry;
  tree_editor->add_directory = add_directory;
  tree_editor->open_directory = open_directory;
  tree_editor->change_dir_prop = change_dir_prop;
  tree_editor->close_directory = close_directory;
  tree_editor->add_file = add_file;
  tree_editor->open_file = open_file;
  tree_editor->apply_textdelta = apply_textdelta;
  tree_editor->change_file_prop = change_file_prop;
  tree_editor->close_file = close_file;
  tree_editor->close_edit = close_edit;

  inner_editor = tree_editor;
  inner_baton = eb;

  if (!server_performs_filtering
      && !depth_as_sticky)
    SVN_ERR(svn_wc__ambient_depth_filter_editor(&inner_editor,
                                                &inner_baton,
                                                wc_ctx->db,
                                                anchor_abspath,
                                                target_basename,
                                                inner_editor,
                                                inner_baton,
                                                result_pool));

  /* Conjoin a cancellation editor with our status editor. */
  SVN_ERR(svn_delta_get_cancellation_editor(cancel_func, cancel_baton,
                                            inner_editor, inner_baton,
                                            editor, edit_baton,
                                            result_pool));

  if (set_locks_baton)
    *set_locks_baton = eb;

  sfb = apr_palloc(result_pool, sizeof(*sfb));
  sfb->db = wc_ctx->db;
  sfb->base_abspath = eb->anchor_abspath;
  sfb->fetch_base = FALSE;

  shim_callbacks->fetch_kind_func = svn_wc__fetch_kind_func;
  shim_callbacks->fetch_props_func = svn_wc__fetch_props_func;
  shim_callbacks->fetch_base_func = svn_wc__fetch_base_func;
  shim_callbacks->fetch_baton = sfb;

  SVN_ERR(svn_editor__insert_shims(editor, edit_baton, *editor, *edit_baton,
                                   NULL, NULL, shim_callbacks,
                                   result_pool, scratch_pool));

  return SVN_NO_ERROR;
}