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
struct catch_errors_args {void* func_args; int /*<<< orphan*/ * func; } ;
typedef  int /*<<< orphan*/  return_mask ;
typedef  enum return_reason { ____Placeholder_return_reason } return_reason ;
typedef  int /*<<< orphan*/  catch_errors_ftype ;

/* Variables and functions */
 int /*<<< orphan*/  catcher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct catch_errors_args*,int*,int*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_catch_errors ; 
 int /*<<< orphan*/  uiout ; 

int
catch_errors (catch_errors_ftype *func, void *func_args, char *errstring,
	      return_mask mask)
{
  int val;
  enum return_reason caught;
  struct catch_errors_args args;
  args.func = func;
  args.func_args = func_args;
  catcher (do_catch_errors, uiout, &args, &val, &caught, errstring, 
	   NULL, mask);
  if (caught != 0)
    return 0;
  return val;
}