#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct baton_apr {int /*<<< orphan*/  pool; int /*<<< orphan*/  file; } ;
typedef  int apr_size_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 TYPE_1__* svn_io_file_getc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_io_file_read (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
read_handler_apr(void *baton, char *buffer, apr_size_t *len)
{
  struct baton_apr *btn = baton;
  svn_error_t *err;

  if (*len == 1)
    {
      err = svn_io_file_getc(buffer, btn->file, btn->pool);
      if (err)
        {
          *len = 0;
          if (APR_STATUS_IS_EOF(err->apr_err))
            {
              svn_error_clear(err);
              err = SVN_NO_ERROR;
            }
        }
    }
  else
    {
      err = svn_io_file_read(btn->file, buffer, len, btn->pool);
      if (err && APR_STATUS_IS_EOF(err->apr_err))
        {
          svn_error_clear(err);
          err = NULL;
        }
    }

  return svn_error_trace(err);
}