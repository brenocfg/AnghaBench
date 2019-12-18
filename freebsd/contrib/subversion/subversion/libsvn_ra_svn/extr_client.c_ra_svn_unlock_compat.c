#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_5__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
struct TYPE_6__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/ * (* svn_ra_lock_callback_t ) (void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_IS_UNLOCK_ERROR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_unsupported_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (void*,char*) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_svn__read_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_string_create (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *ra_svn_unlock_compat(svn_ra_session_t *session,
                                         apr_hash_t *path_tokens,
                                         svn_boolean_t break_lock,
                                         svn_ra_lock_callback_t lock_func,
                                         void *lock_baton,
                                         apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess = session->priv;
  svn_ra_svn_conn_t* conn = sess->conn;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool = svn_pool_create(pool);

  for (hi = apr_hash_first(pool, path_tokens); hi; hi = apr_hash_next(hi))
    {
      const void *key;
      const char *path;
      void *val;
      const svn_string_t *token;
      svn_error_t *err, *callback_err = NULL;

      svn_pool_clear(iterpool);

      apr_hash_this(hi, &key, NULL, &val);
      path = key;
      if (strcmp(val, "") != 0)
        token = svn_string_create(val, iterpool);
      else
        token = NULL;

      SVN_ERR(svn_ra_svn__write_cmd_unlock(conn, iterpool, path, token,
                                           break_lock));

      /* Servers before 1.2 don't support locking.  Check this here. */
      SVN_ERR(handle_unsupported_cmd(handle_auth_request(sess, iterpool),
                                     N_("Server doesn't support the unlock "
                                        "command")));

      err = svn_ra_svn__read_cmd_response(conn, iterpool, "");

      if (err && !SVN_ERR_IS_UNLOCK_ERROR(err))
        return err;

      if (lock_func)
        callback_err = lock_func(lock_baton, path, FALSE, NULL, err, pool);

      svn_error_clear(err);

      if (callback_err)
        return callback_err;
    }

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}