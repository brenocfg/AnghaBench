#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_t ;
struct TYPE_5__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct notify_baton {scalar_t__ had_print_error; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_ERR_IO_PIPE_WRITE_ERROR ; 
 scalar_t__ TRUE ; 
 TYPE_1__* notify_body (struct notify_baton*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_handle_error2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
notify(void *baton, const svn_wc_notify_t *n, apr_pool_t *pool)
{
  struct notify_baton *nb = baton;
  svn_error_t *err;

  err = notify_body(nb, n, pool);

  /* If we had no errors before, print this error to stderr. Else, don't print
     anything.  The user already knows there were some output errors,
     so there is no point in flooding her with an error per notification. */
  if (err && !nb->had_print_error)
    {
      nb->had_print_error = TRUE;
      /* Issue #3014:
       * Don't print anything on broken pipes. The pipe was likely
       * closed by the process at the other end. We expect that
       * process to perform error reporting as necessary.
       *
       * ### This assumes that there is only one error in a chain for
       * ### SVN_ERR_IO_PIPE_WRITE_ERROR. See svn_cmdline_fputs(). */
      if (err->apr_err != SVN_ERR_IO_PIPE_WRITE_ERROR)
        svn_handle_error2(err, stderr, FALSE, "svn: ");
    }
  svn_error_clear(err);
}