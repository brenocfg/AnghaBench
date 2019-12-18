#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serve_params_t ;
typedef  enum connection_handling_mode { ____Placeholder_connection_handling_mode } connection_handling_mode ;
struct TYPE_4__ {int ref_count; int /*<<< orphan*/  usock; int /*<<< orphan*/ * params; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ connection_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_socket_t ;
typedef  int /*<<< orphan*/  apr_proc_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_CHILD_DONE ; 
 int /*<<< orphan*/  APR_NOWAIT ; 
 scalar_t__ APR_STATUS_IS_ECONNABORTED (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_ECONNRESET (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_EINTR (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ apr_proc_wait_all_procs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_socket_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int connection_mode_fork ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 scalar_t__ winservice_is_stopping () ; 

__attribute__((used)) static svn_error_t *
accept_connection(connection_t **connection,
                  apr_socket_t *sock,
                  serve_params_t *params,
                  enum connection_handling_mode handling_mode,
                  apr_pool_t *pool)
{
  apr_status_t status;

  /* Non-standard pool handling.  The main thread never blocks to join
   *         the connection threads so it cannot clean up after each one.  So
   *         separate pools that can be cleared at thread exit are used. */

  apr_pool_t *connection_pool = svn_pool_create(pool);
  *connection = apr_pcalloc(connection_pool, sizeof(**connection));
  (*connection)->pool = connection_pool;
  (*connection)->params = params;
  (*connection)->ref_count = 1;

  do
    {
      #ifdef WIN32
      if (winservice_is_stopping())
        exit(0);
      #endif

      status = apr_socket_accept(&(*connection)->usock, sock,
                                 connection_pool);
      if (handling_mode == connection_mode_fork)
        {
          apr_proc_t proc;

          /* Collect any zombie child processes. */
          while (apr_proc_wait_all_procs(&proc, NULL, NULL, APR_NOWAIT,
            connection_pool) == APR_CHILD_DONE)
            ;
        }
    }
  while (APR_STATUS_IS_EINTR(status)
    || APR_STATUS_IS_ECONNABORTED(status)
    || APR_STATUS_IS_ECONNRESET(status));

  return status
       ? svn_error_wrap_apr(status, _("Can't accept client connection"))
       : SVN_NO_ERROR;
}