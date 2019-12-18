#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_14__ {int /*<<< orphan*/  shim_callbacks; int /*<<< orphan*/  session_url_str; scalar_t__ supports_put_result_checksum; int /*<<< orphan*/  useragent; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_15__ {int /*<<< orphan*/  apply_textdelta_stream; int /*<<< orphan*/  abort_edit; int /*<<< orphan*/  close_edit; int /*<<< orphan*/  close_file; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  open_file; int /*<<< orphan*/  add_file; int /*<<< orphan*/  close_directory; int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  open_directory; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  delete_entry; int /*<<< orphan*/  open_root; } ;
typedef  TYPE_3__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_commit_callback2_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_16__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  deleted_entries; scalar_t__ keep_locks; int /*<<< orphan*/ * lock_tokens; void* callback_baton; int /*<<< orphan*/  callback; int /*<<< orphan*/  revprop_table; TYPE_2__* session; } ;
typedef  TYPE_4__ commit_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_TXN_CLIENT_COMPAT_VERSION ; 
 int /*<<< orphan*/  SVN_PROP_TXN_USER_AGENT ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_EPHEMERAL_TXNPROPS ; 
 int /*<<< orphan*/  SVN_VER_NUMBER ; 
 int /*<<< orphan*/  abort_edit ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
 int /*<<< orphan*/  apply_textdelta_stream ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_dir_prop ; 
 int /*<<< orphan*/  change_file_prop ; 
 int /*<<< orphan*/  close_directory ; 
 int /*<<< orphan*/  close_edit ; 
 int /*<<< orphan*/  close_file ; 
 int /*<<< orphan*/  delete_entry ; 
 int /*<<< orphan*/  open_directory ; 
 int /*<<< orphan*/  open_file ; 
 int /*<<< orphan*/  open_root ; 
 TYPE_3__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_editor__insert_shims (TYPE_3__ const**,void**,TYPE_3__ const*,void*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_prop_hash_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__get_repos_root (TYPE_1__*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__has_capability (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_uri_skip_ancestor (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__get_commit_editor(svn_ra_session_t *ra_session,
                               const svn_delta_editor_t **ret_editor,
                               void **edit_baton,
                               apr_hash_t *revprop_table,
                               svn_commit_callback2_t callback,
                               void *callback_baton,
                               apr_hash_t *lock_tokens,
                               svn_boolean_t keep_locks,
                               apr_pool_t *pool)
{
  svn_ra_serf__session_t *session = ra_session->priv;
  svn_delta_editor_t *editor;
  commit_context_t *ctx;
  const char *repos_root;
  const char *base_relpath;
  svn_boolean_t supports_ephemeral_props;

  ctx = apr_pcalloc(pool, sizeof(*ctx));

  ctx->pool = pool;

  ctx->session = session;

  ctx->revprop_table = svn_prop_hash_dup(revprop_table, pool);

  /* If the server supports ephemeral properties, add some carrying
     interesting version information. */
  SVN_ERR(svn_ra_serf__has_capability(ra_session, &supports_ephemeral_props,
                                      SVN_RA_CAPABILITY_EPHEMERAL_TXNPROPS,
                                      pool));
  if (supports_ephemeral_props)
    {
      svn_hash_sets(ctx->revprop_table,
                    apr_pstrdup(pool, SVN_PROP_TXN_CLIENT_COMPAT_VERSION),
                    svn_string_create(SVN_VER_NUMBER, pool));
      svn_hash_sets(ctx->revprop_table,
                    apr_pstrdup(pool, SVN_PROP_TXN_USER_AGENT),
                    svn_string_create(session->useragent, pool));
    }

  ctx->callback = callback;
  ctx->callback_baton = callback_baton;

  ctx->lock_tokens = (lock_tokens && apr_hash_count(lock_tokens))
                       ? lock_tokens : NULL;
  ctx->keep_locks = keep_locks;

  ctx->deleted_entries = apr_hash_make(ctx->pool);

  editor = svn_delta_default_editor(pool);
  editor->open_root = open_root;
  editor->delete_entry = delete_entry;
  editor->add_directory = add_directory;
  editor->open_directory = open_directory;
  editor->change_dir_prop = change_dir_prop;
  editor->close_directory = close_directory;
  editor->add_file = add_file;
  editor->open_file = open_file;
  editor->apply_textdelta = apply_textdelta;
  editor->change_file_prop = change_file_prop;
  editor->close_file = close_file;
  editor->close_edit = close_edit;
  editor->abort_edit = abort_edit;
  /* Only install the callback that allows streaming PUT request bodies
   * if the server has the necessary capability.  Otherwise, this will
   * fallback to the default implementation using the temporary files.
   * See default_editor.c:apply_textdelta_stream(). */
  if (session->supports_put_result_checksum)
    editor->apply_textdelta_stream = apply_textdelta_stream;

  *ret_editor = editor;
  *edit_baton = ctx;

  SVN_ERR(svn_ra_serf__get_repos_root(ra_session, &repos_root, pool));
  base_relpath = svn_uri_skip_ancestor(repos_root, session->session_url_str,
                                       pool);

  SVN_ERR(svn_editor__insert_shims(ret_editor, edit_baton, *ret_editor,
                                   *edit_baton, repos_root, base_relpath,
                                   session->shim_callbacks, pool, pool));

  return SVN_NO_ERROR;
}