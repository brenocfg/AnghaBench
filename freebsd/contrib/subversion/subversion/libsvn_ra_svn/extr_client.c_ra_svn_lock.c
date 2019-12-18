#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_26__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_2__ svn_ra_svn__session_baton_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
struct TYPE_25__ {int /*<<< orphan*/  list; } ;
struct TYPE_27__ {scalar_t__ kind; TYPE_1__ u; } ;
typedef  TYPE_3__ svn_ra_svn__item_t ;
struct TYPE_28__ {TYPE_2__* priv; } ;
typedef  TYPE_4__ svn_ra_session_t ;
typedef  TYPE_5__* (* svn_ra_lock_callback_t ) (void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_lock_t ;
struct TYPE_29__ {scalar_t__ apr_err; } ;
typedef  TYPE_5__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_MALFORMED_DATA ; 
 scalar_t__ SVN_ERR_RA_SVN_UNKNOWN_CMD ; 
 TYPE_5__* SVN_NO_ERROR ; 
 scalar_t__ SVN_RA_SVN_LIST ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 TYPE_5__* handle_auth_request (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_done_response (TYPE_3__*) ; 
 int /*<<< orphan*/  parse_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_5__* ra_svn_lock_compat (TYPE_4__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_5__* (*) (void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * reparent_path_hash (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_5__*) ; 
 TYPE_5__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_5__* svn_ra_svn__handle_failure_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_tuple (int /*<<< orphan*/ *,char*,char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_svn__read_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static svn_error_t *ra_svn_lock(svn_ra_session_t *session,
                                apr_hash_t *path_revs,
                                const char *comment,
                                svn_boolean_t steal_lock,
                                svn_ra_lock_callback_t lock_func,
                                void *lock_baton,
                                apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess = session->priv;
  svn_ra_svn_conn_t *conn = sess->conn;
  apr_hash_index_t *hi;
  svn_error_t *err;
  apr_pool_t *iterpool = svn_pool_create(pool);

  path_revs = reparent_path_hash(session, path_revs, pool, pool);
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "w((?c)b(!", "lock-many",
                                  comment, steal_lock));

  for (hi = apr_hash_first(pool, path_revs); hi; hi = apr_hash_next(hi))
    {
      const void *key;
      const char *path;
      void *val;
      svn_revnum_t *revnum;

      svn_pool_clear(iterpool);
      apr_hash_this(hi, &key, NULL, &val);
      path = key;
      revnum = val;

      SVN_ERR(svn_ra_svn__write_tuple(conn, iterpool, "c(?r)", path, *revnum));
    }

  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "!))"));

  err = handle_auth_request(sess, pool);

  /* Pre-1.3 servers don't support 'lock-many'. If that fails, fall back
   * to 'lock'. */
  if (err && err->apr_err == SVN_ERR_RA_SVN_UNKNOWN_CMD)
    {
      svn_error_clear(err);
      return ra_svn_lock_compat(session, path_revs, comment, steal_lock,
                                lock_func, lock_baton, pool);
    }

  if (err)
    return err;

  /* Loop over responses to get lock information. */
  for (hi = apr_hash_first(pool, path_revs); hi; hi = apr_hash_next(hi))
    {
      svn_ra_svn__item_t *elt;
      const void *key;
      const char *path;
      svn_error_t *callback_err;
      const char *status;
      svn_lock_t *lock;
      svn_ra_svn__list_t *list;

      apr_hash_this(hi, &key, NULL, NULL);
      path = key;

      svn_pool_clear(iterpool);
      SVN_ERR(svn_ra_svn__read_item(conn, iterpool, &elt));

      /* The server might have encountered some sort of fatal error in
         the middle of the request list.  If this happens, it will
         transmit "done" to end the lock-info early, and then the
         overall command response will talk about the fatal error. */
      if (is_done_response(elt))
        break;

      if (elt->kind != SVN_RA_SVN_LIST)
        return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                                _("Lock response not a list"));

      SVN_ERR(svn_ra_svn__parse_tuple(&elt->u.list, "wl", &status, &list));

      if (strcmp(status, "failure") == 0)
        err = svn_ra_svn__handle_failure_status(list);
      else if (strcmp(status, "success") == 0)
        {
          SVN_ERR(parse_lock(list, iterpool, &lock));
          err = NULL;
        }
      else
        return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                                _("Unknown status for lock command"));

      if (lock_func)
        callback_err = lock_func(lock_baton, path, TRUE,
                                 err ? NULL : lock,
                                 err, iterpool);
      else
        callback_err = SVN_NO_ERROR;

      svn_error_clear(err);

      if (callback_err)
        return callback_err;
    }

  /* If we didn't break early above, and the whole hash was traversed,
     read the final "done" from the server. */
  if (!hi)
    {
      svn_ra_svn__item_t *elt;

      SVN_ERR(svn_ra_svn__read_item(conn, pool, &elt));
      if (!is_done_response(elt))
        return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                                _("Didn't receive end marker for lock "
                                  "responses"));
    }

  SVN_ERR(svn_ra_svn__read_cmd_response(conn, pool, ""));

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}