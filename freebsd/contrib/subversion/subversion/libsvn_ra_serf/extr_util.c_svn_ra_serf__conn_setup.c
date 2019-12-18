#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
struct TYPE_2__ {int /*<<< orphan*/ * session; } ;
typedef  TYPE_1__ svn_ra_serf__connection_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_socket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  conn_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  save_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 

apr_status_t
svn_ra_serf__conn_setup(apr_socket_t *sock,
                        serf_bucket_t **read_bkt,
                        serf_bucket_t **write_bkt,
                        void *baton,
                        apr_pool_t *pool)
{
  svn_ra_serf__connection_t *conn = baton;
  svn_ra_serf__session_t *session = conn->session;
  svn_error_t *err;

  err = svn_error_trace(conn_setup(sock,
                                   read_bkt,
                                   write_bkt,
                                   baton,
                                   pool));
  return save_error(session, err);
}