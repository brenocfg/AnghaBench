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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION_NO_RETURN () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ svn_error_abort_on_malfunction ; 
 scalar_t__ svn_error_get_malfunction_handler () ; 
 int /*<<< orphan*/  svn_handle_error2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
default_warning_func(void *baton, svn_error_t *err)
{
  /* The one unforgiveable sin is to fail silently.  Dumping to stderr
     or /dev/tty is not acceptable default behavior for server
     processes, since those may both be equivalent to /dev/null.

     That said, be a good citizen and print something anyway, in case it goes
     somewhere, and our caller hasn't overridden the abort() call.
   */
  if (svn_error_get_malfunction_handler()
      == svn_error_abort_on_malfunction)
    /* ### TODO: extend the malfunction API such that non-abort()ing consumers
       ### also get the information on ERR. */
    svn_handle_error2(err, stderr, FALSE /* fatal */, "svn: fs-loader: ");
  SVN_ERR_MALFUNCTION_NO_RETURN();
}