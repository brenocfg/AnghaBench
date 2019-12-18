#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pool; TYPE_3__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
struct TYPE_9__ {TYPE_1__* fs_path; int /*<<< orphan*/  repos_url; int /*<<< orphan*/  repos; int /*<<< orphan*/  useragent; int /*<<< orphan*/  username; int /*<<< orphan*/  fs; } ;
typedef  TYPE_3__ svn_ra_local__session_baton_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_commit_callback2_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct deltify_etc_baton {void* commit_baton; int /*<<< orphan*/  commit_cb; int /*<<< orphan*/ * lock_tokens; int /*<<< orphan*/  fspath_base; int /*<<< orphan*/  repos; int /*<<< orphan*/  fs; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_TXN_CLIENT_COMPAT_VERSION ; 
 int /*<<< orphan*/  SVN_PROP_TXN_USER_AGENT ; 
 int /*<<< orphan*/  SVN_VER_NUMBER ; 
 int /*<<< orphan*/  apply_lock_tokens (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct deltify_etc_baton* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  deltify_etc ; 
 int /*<<< orphan*/  get_username (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remap_commit_callback (int /*<<< orphan*/ *,void**,TYPE_2__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_path_uri_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_get_commit_editor5 (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct deltify_etc_baton*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_string_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_ra_local__get_commit_editor(svn_ra_session_t *session,
                                const svn_delta_editor_t **editor,
                                void **edit_baton,
                                apr_hash_t *revprop_table,
                                svn_commit_callback2_t callback,
                                void *callback_baton,
                                apr_hash_t *lock_tokens,
                                svn_boolean_t keep_locks,
                                apr_pool_t *pool)
{
  svn_ra_local__session_baton_t *sess = session->priv;
  struct deltify_etc_baton *deb = apr_palloc(pool, sizeof(*deb));

  /* Set repos_root_url in commit info */
  remap_commit_callback(&callback, &callback_baton, session,
                        callback, callback_baton, pool);

  /* Prepare the baton for deltify_etc()  */
  deb->fs = sess->fs;
  deb->repos = sess->repos;
  deb->fspath_base = sess->fs_path->data;
  if (! keep_locks)
    deb->lock_tokens = lock_tokens;
  else
    deb->lock_tokens = NULL;
  deb->commit_cb = callback;
  deb->commit_baton = callback_baton;

  SVN_ERR(get_username(session, pool));

  /* If there are lock tokens to add, do so. */
  SVN_ERR(apply_lock_tokens(sess->fs, sess->fs_path->data, lock_tokens,
                            session->pool, pool));

  /* Copy the revprops table so we can add the username. */
  revprop_table = apr_hash_copy(pool, revprop_table);
  svn_hash_sets(revprop_table, SVN_PROP_REVISION_AUTHOR,
                svn_string_create(sess->username, pool));
  svn_hash_sets(revprop_table, SVN_PROP_TXN_CLIENT_COMPAT_VERSION,
                svn_string_create(SVN_VER_NUMBER, pool));
  svn_hash_sets(revprop_table, SVN_PROP_TXN_USER_AGENT,
                svn_string_create(sess->useragent, pool));

  /* Get the repos commit-editor */
  return svn_repos_get_commit_editor5
         (editor, edit_baton, sess->repos, NULL,
          svn_path_uri_decode(sess->repos_url, pool), sess->fs_path->data,
          revprop_table, deltify_etc, deb, NULL, NULL, pool);
}