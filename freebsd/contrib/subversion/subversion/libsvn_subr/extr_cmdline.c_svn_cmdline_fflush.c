#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  SVN_ERR_IO_PIPE_WRITE_ERROR ; 
 int /*<<< orphan*/  SVN_ERR_IO_WRITE_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN__APR_STATUS_IS_EPIPE (scalar_t__) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_get_os_error () ; 
 scalar_t__ errno ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_wrap_apr (scalar_t__,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_cmdline_fflush(FILE *stream)
{
  /* See comment in svn_cmdline_fputs about use of errno and stdio. */
  errno = 0;
  if (fflush(stream) == EOF)
    {
      if (apr_get_os_error()) /* is errno on POSIX */
        {
          /* ### Issue #3014: Return a specific error for broken pipes,
           * ### with a single element in the error chain. */
          if (SVN__APR_STATUS_IS_EPIPE(apr_get_os_error()))
            return svn_error_create(SVN_ERR_IO_PIPE_WRITE_ERROR, NULL, NULL);
          else
            return svn_error_wrap_apr(apr_get_os_error(), _("Write error"));
        }
      else
        return svn_error_create(SVN_ERR_IO_WRITE_ERROR, NULL, NULL);
    }

  return SVN_NO_ERROR;
}