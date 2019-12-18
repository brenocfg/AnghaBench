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
struct TYPE_6__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
struct TYPE_7__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_editor_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ensure_exact_server_parent (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_unsupported_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_replay (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn_drive_editor2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *ra_svn_replay(svn_ra_session_t *session,
                                  svn_revnum_t revision,
                                  svn_revnum_t low_water_mark,
                                  svn_boolean_t send_deltas,
                                  const svn_delta_editor_t *editor,
                                  void *edit_baton,
                                  apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess = session->priv;

  /* Complex EDITOR callbacks may rely on client and server parent path
     being in sync. */
  SVN_ERR(ensure_exact_server_parent(session, pool));
  SVN_ERR(svn_ra_svn__write_cmd_replay(sess->conn, pool, revision,
                                       low_water_mark, send_deltas));

  SVN_ERR(handle_unsupported_cmd(handle_auth_request(sess, pool),
                                 N_("Server doesn't support the replay "
                                    "command")));

  SVN_ERR(svn_ra_svn_drive_editor2(sess->conn, pool, editor, edit_baton,
                                   NULL, TRUE));

  return svn_error_trace(svn_ra_svn__read_cmd_response(sess->conn, pool, ""));
}