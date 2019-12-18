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
struct TYPE_6__ {int num_conns; int /*<<< orphan*/  pool; TYPE_2__** conns; int /*<<< orphan*/  session_url; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_status_t ;
struct TYPE_7__ {int last_status_code; int /*<<< orphan*/  conn; TYPE_1__* session; int /*<<< orphan*/  bkt_alloc; } ;

/* Variables and functions */
 int REQS_PER_CONN ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serf_bucket_allocator_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ serf_connection_create2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__conn_closed ; 
 int /*<<< orphan*/  svn_ra_serf__conn_setup ; 
 int /*<<< orphan*/ * svn_ra_serf__wrap_err (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_connection_if_needed(svn_ra_serf__session_t *sess, int num_active_reqs)
{
  /* For each REQS_PER_CONN outstanding requests open a new connection, with
   * a minimum of 1 extra connection. */
  if (sess->num_conns == 1 ||
      ((num_active_reqs / REQS_PER_CONN) > sess->num_conns))
    {
      int cur = sess->num_conns;
      apr_status_t status;

      sess->conns[cur] = apr_pcalloc(sess->pool, sizeof(*sess->conns[cur]));
      sess->conns[cur]->bkt_alloc = serf_bucket_allocator_create(sess->pool,
                                                                 NULL, NULL);
      sess->conns[cur]->last_status_code = -1;
      sess->conns[cur]->session = sess;
      status = serf_connection_create2(&sess->conns[cur]->conn,
                                       sess->context,
                                       sess->session_url,
                                       svn_ra_serf__conn_setup,
                                       sess->conns[cur],
                                       svn_ra_serf__conn_closed,
                                       sess->conns[cur],
                                       sess->pool);
      if (status)
        return svn_ra_serf__wrap_err(status, NULL);

      sess->num_conns++;
    }

  return SVN_NO_ERROR;
}