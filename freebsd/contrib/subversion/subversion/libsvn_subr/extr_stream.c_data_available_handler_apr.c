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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct baton_apr {int /*<<< orphan*/  file; int /*<<< orphan*/  pool; } ;
typedef  scalar_t__ apr_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  f; } ;
struct TYPE_5__ {int /*<<< orphan*/  reqevents; int /*<<< orphan*/  p; TYPE_1__ desc; int /*<<< orphan*/  desc_type; } ;
typedef  TYPE_2__ apr_pollfd_t ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  APR_POLLIN ; 
 int /*<<< orphan*/  APR_POLL_FILE ; 
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ APR_STATUS_IS_TIMEUP (scalar_t__) ; 
 scalar_t__ APR_SUCCESS ; 
 int FALSE ; 
 scalar_t__ PeekNamedPipe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_STREAM_NOT_SUPPORTED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * _ (char*) ; 
 scalar_t__ apr_get_os_error () ; 
 scalar_t__ apr_os_file_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_poll (TYPE_2__*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
data_available_handler_apr(void *baton, svn_boolean_t *data_available)
{
  struct baton_apr *btn = baton;
  apr_status_t status;
#if !defined(WIN32) || APR_FILES_AS_SOCKETS
  apr_pollfd_t pfd;
  int n;

  pfd.desc_type = APR_POLL_FILE;
  pfd.desc.f = btn->file;
  pfd.p = btn->pool; /* If we had a scratch pool... Luckily apr doesn't
                        store anything in this pool at this time */
  pfd.reqevents = APR_POLLIN;

  status = apr_poll(&pfd, 1, &n, 0);

  if (status == APR_SUCCESS)
    {
      *data_available = (n > 0);
      return SVN_NO_ERROR;
    }
  else if (APR_STATUS_IS_EOF(status) || APR_STATUS_IS_TIMEUP(status))
    {
      *data_available = FALSE;
      return SVN_NO_ERROR;
    }
  else
    {
      return svn_error_create(SVN_ERR_STREAM_NOT_SUPPORTED,
                              svn_error_wrap_apr(
                                  status,
                                  _("Polling for available data on filestream "
                                    "failed")),
                              NULL);
    }
#else
  HANDLE h;
  DWORD dwAvail;
  status = apr_os_file_get(&h, btn->file);

  if (status)
    return svn_error_wrap_apr(status, NULL);

  if (PeekNamedPipe(h, NULL, 0, NULL, &dwAvail, NULL))
    {
      *data_available = (dwAvail > 0);
      return SVN_NO_ERROR;
    }

  return svn_error_create(SVN_ERR_STREAM_NOT_SUPPORTED,
                          svn_error_wrap_apr(apr_get_os_error(), NULL),
                          _("Windows doesn't support polling on files"));
#endif
}