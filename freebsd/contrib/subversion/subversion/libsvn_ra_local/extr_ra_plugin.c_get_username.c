#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pool; TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_6__ {char* username; int /*<<< orphan*/  fs; scalar_t__ auth_baton; int /*<<< orphan*/  uuid; } ;
typedef  TYPE_2__ svn_ra_local__session_baton_t ;
typedef  int /*<<< orphan*/  svn_fs_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_auth_iterstate_t ;
struct TYPE_7__ {scalar_t__ username; } ;
typedef  TYPE_3__ svn_auth_cred_username_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_AUTH_CRED_USERNAME ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_pstrdup (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cleanup_access ; 
 int /*<<< orphan*/  svn_auth_first_credentials (void**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_auth_save_credentials (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_create_access (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_set_access (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_username(svn_ra_session_t *session,
             apr_pool_t *scratch_pool)
{
  svn_ra_local__session_baton_t *sess = session->priv;

  /* If we've already found the username don't ask for it again. */
  if (! sess->username)
    {
      /* Get a username somehow, so we have some svn:author property to
         attach to a commit. */
      if (sess->auth_baton)
        {
          void *creds;
          svn_auth_cred_username_t *username_creds;
          svn_auth_iterstate_t *iterstate;

          SVN_ERR(svn_auth_first_credentials(&creds, &iterstate,
                                             SVN_AUTH_CRED_USERNAME,
                                             sess->uuid, /* realmstring */
                                             sess->auth_baton,
                                             scratch_pool));

          /* No point in calling next_creds(), since that assumes that the
             first_creds() somehow failed to authenticate.  But there's no
             challenge going on, so we use whatever creds we get back on
             the first try. */
          username_creds = creds;
          if (username_creds && username_creds->username)
            {
              sess->username = apr_pstrdup(session->pool,
                                           username_creds->username);
              svn_error_clear(svn_auth_save_credentials(iterstate,
                                                        scratch_pool));
            }
          else
            sess->username = "";
        }
      else
        sess->username = "";
    }

  /* If we have a real username, attach it to the filesystem so that it can
     be used to validate locks.  Even if there already is a user context
     associated, it may contain irrelevant lock tokens, so always create a new.
  */
  if (*sess->username)
    {
      svn_fs_access_t *access_ctx;

      SVN_ERR(svn_fs_create_access(&access_ctx, sess->username,
                                   session->pool));
      SVN_ERR(svn_fs_set_access(sess->fs, access_ctx));

      /* Make sure this context is disassociated when the pool gets
         destroyed. */
      apr_pool_cleanup_register(session->pool, sess->fs, cleanup_access,
                                apr_pool_cleanup_null);
    }

  return SVN_NO_ERROR;
}