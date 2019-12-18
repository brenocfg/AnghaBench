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
 int /*<<< orphan*/ * malfunction_handler (int /*<<< orphan*/ ,char const*,int,char const*) ; 

svn_error_t *
svn_error__malfunction(svn_boolean_t can_return,
                       const char *file, int line,
                       const char *expr)
{
  return malfunction_handler(can_return, file, line, expr);
}