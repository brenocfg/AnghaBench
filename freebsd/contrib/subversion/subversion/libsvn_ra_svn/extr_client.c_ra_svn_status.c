#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_7__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
struct TYPE_8__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_ra_reporter3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEPTH_TO_RECURSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  ensure_exact_server_parent (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_svn_get_reporter (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,void**) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_status (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *ra_svn_status(svn_ra_session_t *session,
                                  const svn_ra_reporter3_t **reporter,
                                  void **report_baton,
                                  const char *target, svn_revnum_t rev,
                                  svn_depth_t depth,
                                  const svn_delta_editor_t *status_editor,
                                  void *status_baton, apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess_baton = session->priv;
  svn_ra_svn_conn_t *conn = sess_baton->conn;
  svn_boolean_t recurse = DEPTH_TO_RECURSE(depth);

  /* Callbacks may assume that all data is relative the sessions's URL. */
  SVN_ERR(ensure_exact_server_parent(session, pool));

  /* Tell the server we want to start a status operation. */
  SVN_ERR(svn_ra_svn__write_cmd_status(conn, pool, target, recurse, rev,
                                       depth));
  SVN_ERR(handle_auth_request(sess_baton, pool));

  /* Fetch a reporter for the caller to drive.  The reporter will drive
   * status_editor upon finish_report(). */
  SVN_ERR(ra_svn_get_reporter(sess_baton, pool, status_editor, status_baton,
                              target, depth, reporter, report_baton));
  return SVN_NO_ERROR;
}