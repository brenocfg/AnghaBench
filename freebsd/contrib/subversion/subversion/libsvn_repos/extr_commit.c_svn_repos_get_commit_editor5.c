#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  (* svn_repos_authz_callback_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {struct edit_baton* fetch_baton; int /*<<< orphan*/  fetch_base_func; int /*<<< orphan*/  fetch_kind_func; int /*<<< orphan*/  fetch_props_func; } ;
typedef  TYPE_1__ svn_delta_shim_callbacks_t ;
struct TYPE_10__ {int /*<<< orphan*/  abort_edit; int /*<<< orphan*/  close_edit; int /*<<< orphan*/  change_file_prop; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  close_file; int /*<<< orphan*/  open_file; int /*<<< orphan*/  add_file; int /*<<< orphan*/  change_dir_prop; int /*<<< orphan*/  open_directory; int /*<<< orphan*/  add_directory; int /*<<< orphan*/  delete_entry; int /*<<< orphan*/  open_root; } ;
typedef  TYPE_2__ svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_commit_callback2_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct edit_baton {char const* repos_url_decoded; int /*<<< orphan*/  base_path; int /*<<< orphan*/  txn_owner; int /*<<< orphan*/ * txn; int /*<<< orphan*/  fs; int /*<<< orphan*/  repos_name; int /*<<< orphan*/ * repos; void* authz_baton; int /*<<< orphan*/  (* authz_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ;void* commit_callback_baton; int /*<<< orphan*/  commit_callback; int /*<<< orphan*/  revprop_table; int /*<<< orphan*/ * pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_AUTHZ_UNWRITABLE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  abort_edit ; 
 int /*<<< orphan*/  add_directory ; 
 int /*<<< orphan*/  add_file ; 
 int /*<<< orphan*/  apply_textdelta ; 
 struct edit_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  change_dir_prop ; 
 int /*<<< orphan*/  change_file_prop ; 
 int /*<<< orphan*/  close_edit ; 
 int /*<<< orphan*/  close_file ; 
 int /*<<< orphan*/  delete_entry ; 
 int /*<<< orphan*/  fetch_base_func ; 
 int /*<<< orphan*/  fetch_kind_func ; 
 int /*<<< orphan*/  fetch_props_func ; 
 int /*<<< orphan*/  open_directory ; 
 int /*<<< orphan*/  open_file ; 
 int /*<<< orphan*/  open_root ; 
 int /*<<< orphan*/  svn_authz_write ; 
 TYPE_2__* svn_delta_default_editor (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_delta_shim_callbacks_default (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_editor__insert_shims (TYPE_2__ const**,void**,TYPE_2__ const*,void*,char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_fspath__canonicalize (char const*,int /*<<< orphan*/ *) ; 
 char* svn_path_uri_encode (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_hash_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_get_commit_editor5(const svn_delta_editor_t **editor,
                             void **edit_baton,
                             svn_repos_t *repos,
                             svn_fs_txn_t *txn,
                             const char *repos_url_decoded,
                             const char *base_path,
                             apr_hash_t *revprop_table,
                             svn_commit_callback2_t commit_callback,
                             void *commit_baton,
                             svn_repos_authz_callback_t authz_callback,
                             void *authz_baton,
                             apr_pool_t *pool)
{
  svn_delta_editor_t *e;
  apr_pool_t *subpool = svn_pool_create(pool);
  struct edit_baton *eb;
  svn_delta_shim_callbacks_t *shim_callbacks =
                                    svn_delta_shim_callbacks_default(pool);
  const char *repos_url = svn_path_uri_encode(repos_url_decoded, pool);

  /* Do a global authz access lookup.  Users with no write access
     whatsoever to the repository don't get a commit editor. */
  if (authz_callback)
    {
      svn_boolean_t allowed;

      SVN_ERR(authz_callback(svn_authz_write, &allowed, NULL, NULL,
                             authz_baton, pool));
      if (!allowed)
        return svn_error_create(SVN_ERR_AUTHZ_UNWRITABLE, NULL,
                                "Not authorized to open a commit editor.");
    }

  /* Allocate the structures. */
  e = svn_delta_default_editor(pool);
  eb = apr_pcalloc(subpool, sizeof(*eb));

  /* Set up the editor. */
  e->open_root         = open_root;
  e->delete_entry      = delete_entry;
  e->add_directory     = add_directory;
  e->open_directory    = open_directory;
  e->change_dir_prop   = change_dir_prop;
  e->add_file          = add_file;
  e->open_file         = open_file;
  e->close_file        = close_file;
  e->apply_textdelta   = apply_textdelta;
  e->change_file_prop  = change_file_prop;
  e->close_edit        = close_edit;
  e->abort_edit        = abort_edit;

  /* Set up the edit baton. */
  eb->pool = subpool;
  eb->revprop_table = svn_prop_hash_dup(revprop_table, subpool);
  eb->commit_callback = commit_callback;
  eb->commit_callback_baton = commit_baton;
  eb->authz_callback = authz_callback;
  eb->authz_baton = authz_baton;
  eb->base_path = svn_fspath__canonicalize(base_path, subpool);
  eb->repos = repos;
  eb->repos_url_decoded = repos_url_decoded;
  eb->repos_name = svn_dirent_basename(svn_repos_path(repos, subpool),
                                       subpool);
  eb->fs = svn_repos_fs(repos);
  eb->txn = txn;
  eb->txn_owner = txn == NULL;

  *edit_baton = eb;
  *editor = e;

  shim_callbacks->fetch_props_func = fetch_props_func;
  shim_callbacks->fetch_kind_func = fetch_kind_func;
  shim_callbacks->fetch_base_func = fetch_base_func;
  shim_callbacks->fetch_baton = eb;

  SVN_ERR(svn_editor__insert_shims(editor, edit_baton, *editor, *edit_baton,
                                   repos_url, eb->base_path,
                                   shim_callbacks, pool, pool));

  return SVN_NO_ERROR;
}