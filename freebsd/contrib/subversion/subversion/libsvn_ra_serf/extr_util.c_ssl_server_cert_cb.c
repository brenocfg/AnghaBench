#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ svn_ra_serf__session_t ;
struct TYPE_5__ {TYPE_1__* session; } ;
typedef  TYPE_2__ svn_ra_serf__connection_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_ssl_certificate_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  save_error (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_server_cert (void*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t
ssl_server_cert_cb(void *baton, int failures,
                const serf_ssl_certificate_t *cert)
{
  svn_ra_serf__connection_t *conn = baton;
  svn_ra_serf__session_t *session = conn->session;
  apr_pool_t *subpool;
  svn_error_t *err;

  subpool = svn_pool_create(session->pool);
  err = svn_error_trace(ssl_server_cert(baton, failures, cert, subpool));
  svn_pool_destroy(subpool);

  return save_error(session, err);
}