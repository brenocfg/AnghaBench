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
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * svn_error_raise_on_malfunction (int /*<<< orphan*/ ,char const*,int,char const*) ; 
 int /*<<< orphan*/  svn_handle_error2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

svn_error_t *
svn_error_abort_on_malfunction(svn_boolean_t can_return,
                               const char *file, int line,
                               const char *expr)
{
  svn_error_t *err = svn_error_raise_on_malfunction(TRUE, file, line, expr);

  svn_handle_error2(err, stderr, FALSE, "svn: ");
  abort();
  return err;  /* Not reached. */
}