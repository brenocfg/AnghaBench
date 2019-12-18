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
struct ui_out {int dummy; } ;
typedef  int /*<<< orphan*/  return_mask ;
typedef  enum return_reason { ____Placeholder_return_reason } return_reason ;
typedef  int /*<<< orphan*/  catch_exceptions_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  catcher (int /*<<< orphan*/ *,struct ui_out*,void*,int*,int*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

int
catch_exceptions (struct ui_out *uiout,
		  catch_exceptions_ftype *func,
		  void *func_args,
		  char *errstring,
		  return_mask mask)
{
  int val;
  enum return_reason caught;
  catcher (func, uiout, func_args, &val, &caught, errstring, NULL, mask);
  gdb_assert (val >= 0);
  gdb_assert (caught <= 0);
  if (caught < 0)
    return caught;
  return val;
}