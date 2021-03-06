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
struct TYPE_5__ {int /*<<< orphan*/ * shim_callbacks; } ;
typedef  TYPE_1__ svn_ra_svn_conn_t ;
struct TYPE_6__ {TYPE_1__* conn; } ;
typedef  TYPE_2__ svn_ra_svn__session_baton_t ;
struct TYPE_7__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_delta_shim_callbacks_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
ra_svn_register_editor_shim_callbacks(svn_ra_session_t *session,
                                      svn_delta_shim_callbacks_t *callbacks)
{
  svn_ra_svn__session_baton_t *sess_baton = session->priv;
  svn_ra_svn_conn_t *conn = sess_baton->conn;

  conn->shim_callbacks = callbacks;

  return SVN_NO_ERROR;
}