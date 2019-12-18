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
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  SVN_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  getenv (char*) ; 

__attribute__((used)) static apr_status_t err_abort(void *data)
{
  svn_error_t *err = data;  /* For easy viewing in a debugger */
  SVN_UNUSED(err);

  if (!getenv("SVN_DBG_NO_ABORT_ON_ERROR_LEAK"))
    abort();
  return APR_SUCCESS;
}