#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_6__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
struct TYPE_7__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_unsupported_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* reparent_path (TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_get_deleted_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
ra_svn_get_deleted_rev(svn_ra_session_t *session,
                       const char *path,
                       svn_revnum_t peg_revision,
                       svn_revnum_t end_revision,
                       svn_revnum_t *revision_deleted,
                       apr_pool_t *pool)

{
  svn_ra_svn__session_baton_t *sess_baton = session->priv;
  svn_ra_svn_conn_t *conn = sess_baton->conn;

  path = reparent_path(session, path, pool);

  /* Transmit the parameters. */
  SVN_ERR(svn_ra_svn__write_cmd_get_deleted_rev(conn, pool, path,
                                               peg_revision, end_revision));

  /* Servers before 1.6 don't support this command.  Check for this here. */
  SVN_ERR(handle_unsupported_cmd(handle_auth_request(sess_baton, pool),
                                 N_("'get-deleted-rev' not implemented")));

  return svn_error_trace(svn_ra_svn__read_cmd_response(conn, pool, "r",
                                                       revision_deleted));
}