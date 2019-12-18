#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_14__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  auth_baton; int /*<<< orphan*/  callbacks_baton; int /*<<< orphan*/  callbacks; int /*<<< orphan*/  config; int /*<<< orphan*/  tunnel_argv; int /*<<< orphan*/  tunnel_name; int /*<<< orphan*/ * conn; TYPE_2__* parent; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
struct TYPE_15__ {int /*<<< orphan*/  server_url; } ;
typedef  TYPE_2__ svn_ra_svn__parent_t ;
struct TYPE_16__ {TYPE_1__* priv; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ svn_ra_session_t ;
struct TYPE_17__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_uri_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_RA_SVN_UNKNOWN_CMD ; 
 TYPE_4__* SVN_NO_ERROR ; 
 TYPE_4__* handle_auth_request (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* open_session (TYPE_1__**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* parse_url (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_reparent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_set (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_error_t *
reparent_server(svn_ra_session_t *ra_session,
                const char *url,
                apr_pool_t *scratch_pool)
{
  svn_ra_svn__session_baton_t *sess = ra_session->priv;
  svn_ra_svn__parent_t *parent = sess->parent;
  svn_ra_svn_conn_t *conn = sess->conn;
  svn_error_t *err;
  apr_pool_t *sess_pool;
  svn_ra_svn__session_baton_t *new_sess;
  apr_uri_t uri;

  /* Send the request to the server. */
  SVN_ERR(svn_ra_svn__write_cmd_reparent(conn, scratch_pool, url));
  err = handle_auth_request(sess, scratch_pool);
  if (! err)
    {
      SVN_ERR(svn_ra_svn__read_cmd_response(conn, scratch_pool, ""));
      svn_stringbuf_set(parent->server_url, url);
      return SVN_NO_ERROR;
    }
  else if (err->apr_err != SVN_ERR_RA_SVN_UNKNOWN_CMD)
    return err;

  /* Servers before 1.4 doesn't support this command; try to reconnect
     instead. */
  svn_error_clear(err);
  /* Create a new subpool of the RA session pool. */
  sess_pool = svn_pool_create(ra_session->pool);
  err = parse_url(url, &uri, sess_pool);
  if (! err)
    err = open_session(&new_sess, url, &uri, sess->tunnel_name, sess->tunnel_argv,
                       sess->config, sess->callbacks, sess->callbacks_baton,
                       sess->auth_baton, sess_pool, sess_pool);
  /* We destroy the new session pool on error, since it is allocated in
     the main session pool. */
  if (err)
    {
      svn_pool_destroy(sess_pool);
      return err;
    }

  /* We have a new connection, assign it and destroy the old. */
  ra_session->priv = new_sess;
  svn_pool_destroy(sess->pool);

  return SVN_NO_ERROR;
}