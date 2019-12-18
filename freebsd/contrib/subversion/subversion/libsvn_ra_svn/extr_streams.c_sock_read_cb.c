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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ sock_baton_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int apr_interval_time_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_STATUS_IS_EOF (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_socket_recv (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_socket_timeout_get (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  apr_socket_timeout_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
sock_read_cb(void *baton, char *buffer, apr_size_t *len)
{
  sock_baton_t *b = baton;
  apr_status_t status;
  apr_interval_time_t interval;

  status = apr_socket_timeout_get(b->sock, &interval);
  if (status)
    return svn_error_wrap_apr(status, _("Can't get socket timeout"));

  /* Always block on read.
   * During pipelining, we set the timeout to 0 for some write
   * operations so that we can try them without blocking. If APR had
   * separate timeouts for read and write, we would only set the
   * write timeout, but it doesn't. So here, we revert back to blocking.
   */
  apr_socket_timeout_set(b->sock, -1);
  status = apr_socket_recv(b->sock, buffer, len);
  apr_socket_timeout_set(b->sock, interval);

  if (status && !APR_STATUS_IS_EOF(status))
    return svn_error_wrap_apr(status, _("Can't read from connection"));
  return SVN_NO_ERROR;
}