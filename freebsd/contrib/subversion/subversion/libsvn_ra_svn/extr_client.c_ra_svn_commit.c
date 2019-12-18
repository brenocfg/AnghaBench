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
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_14__ {char* useragent; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_2__ svn_ra_svn__session_baton_t ;
struct TYPE_15__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_commit_callback2_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_16__ {void* callback_baton; int /*<<< orphan*/  callback; int /*<<< orphan*/ * new_rev; int /*<<< orphan*/ * pool; TYPE_2__* sess_baton; } ;
typedef  TYPE_4__ ra_svn_commit_callback_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_PROPERTY_VALUE ; 
 int /*<<< orphan*/  SVN_ERR_RA_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_LOG ; 
 int /*<<< orphan*/  SVN_PROP_TXN_CLIENT_COMPAT_VERSION ; 
 int /*<<< orphan*/  SVN_PROP_TXN_USER_AGENT ; 
 int /*<<< orphan*/  SVN_RA_SVN_CAP_COMMIT_REVPROPS ; 
 int /*<<< orphan*/  SVN_RA_SVN_CAP_EPHEMERAL_TXNPROPS ; 
 char* SVN_VER_NUMBER ; 
 int /*<<< orphan*/  _ (char*) ; 
 int apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 TYPE_4__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ensure_exact_server_parent (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_svn_end_commit ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_svn__write_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_ra_svn_get_editor (int /*<<< orphan*/  const**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ svn_ra_svn_has_capability (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_string_create (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *ra_svn_commit(svn_ra_session_t *session,
                                  const svn_delta_editor_t **editor,
                                  void **edit_baton,
                                  apr_hash_t *revprop_table,
                                  svn_commit_callback2_t callback,
                                  void *callback_baton,
                                  apr_hash_t *lock_tokens,
                                  svn_boolean_t keep_locks,
                                  apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess_baton = session->priv;
  svn_ra_svn_conn_t *conn = sess_baton->conn;
  ra_svn_commit_callback_baton_t *ccb;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool;
  const svn_string_t *log_msg = svn_hash_gets(revprop_table,
                                              SVN_PROP_REVISION_LOG);

  if (log_msg == NULL &&
      ! svn_ra_svn_has_capability(conn, SVN_RA_SVN_CAP_COMMIT_REVPROPS))
    {
      return svn_error_createf(SVN_ERR_BAD_PROPERTY_VALUE, NULL,
                               _("ra_svn does not support not specifying "
                                 "a log message with pre-1.5 servers; "
                                 "consider passing an empty one, or upgrading "
                                 "the server"));
    }
  else if (log_msg == NULL)
    /* 1.5+ server.  Set LOG_MSG to something, since the 'logmsg' argument
       to the 'commit' protocol command is non-optional; on the server side,
       only REVPROP_TABLE will be used, and LOG_MSG will be ignored.  The
       "svn:log" member of REVPROP_TABLE table is NULL, therefore the commit
       will have a NULL log message (not just "", really NULL).

       svnserve 1.5.x+ has always ignored LOG_MSG when REVPROP_TABLE was
       present; this was elevated to a protocol promise in r1498550 (and
       later documented in this comment) in order to fix the segmentation
       fault bug described in the log message of r1498550.*/
    log_msg = svn_string_create("", pool);

  /* If we're sending revprops other than svn:log, make sure the server won't
     silently ignore them. */
  if (apr_hash_count(revprop_table) > 1 &&
      ! svn_ra_svn_has_capability(conn, SVN_RA_SVN_CAP_COMMIT_REVPROPS))
    return svn_error_create(SVN_ERR_RA_NOT_IMPLEMENTED, NULL,
                            _("Server doesn't support setting arbitrary "
                              "revision properties during commit"));

  /* If the server supports ephemeral txnprops, add the one that
     reports the client's version level string. */
  if (svn_ra_svn_has_capability(conn, SVN_RA_SVN_CAP_COMMIT_REVPROPS) &&
      svn_ra_svn_has_capability(conn, SVN_RA_SVN_CAP_EPHEMERAL_TXNPROPS))
    {
      svn_hash_sets(revprop_table, SVN_PROP_TXN_CLIENT_COMPAT_VERSION,
                    svn_string_create(SVN_VER_NUMBER, pool));
      svn_hash_sets(revprop_table, SVN_PROP_TXN_USER_AGENT,
                    svn_string_create(sess_baton->useragent, pool));
    }

  /* Callbacks may assume that all data is relative the sessions's URL. */
  SVN_ERR(ensure_exact_server_parent(session, pool));

  /* Tell the server we're starting the commit.
     Send log message here for backwards compatibility with servers
     before 1.5. */
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "w(c(!", "commit",
                                  log_msg->data));
  if (lock_tokens)
    {
      iterpool = svn_pool_create(pool);
      for (hi = apr_hash_first(pool, lock_tokens); hi; hi = apr_hash_next(hi))
        {
          const void *key;
          void *val;
          const char *path, *token;

          svn_pool_clear(iterpool);
          apr_hash_this(hi, &key, NULL, &val);
          path = key;
          token = val;
          SVN_ERR(svn_ra_svn__write_tuple(conn, iterpool, "cc", path, token));
        }
      svn_pool_destroy(iterpool);
    }
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "!)b(!", keep_locks));
  SVN_ERR(svn_ra_svn__write_proplist(conn, pool, revprop_table));
  SVN_ERR(svn_ra_svn__write_tuple(conn, pool, "!))"));
  SVN_ERR(handle_auth_request(sess_baton, pool));
  SVN_ERR(svn_ra_svn__read_cmd_response(conn, pool, ""));

  /* Remember a few arguments for when the commit is over. */
  ccb = apr_palloc(pool, sizeof(*ccb));
  ccb->sess_baton = sess_baton;
  ccb->pool = pool;
  ccb->new_rev = NULL;
  ccb->callback = callback;
  ccb->callback_baton = callback_baton;

  /* Fetch an editor for the caller to drive.  The editor will call
   * ra_svn_end_commit() upon close_edit(), at which point we'll fill
   * in the new_rev, committed_date, and committed_author values. */
  svn_ra_svn_get_editor(editor, edit_baton, conn, pool,
                        ra_svn_end_commit, ccb);
  return SVN_NO_ERROR;
}