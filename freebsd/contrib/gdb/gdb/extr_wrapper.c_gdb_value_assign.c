#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct TYPE_4__ {scalar_t__ pointer; } ;
struct gdb_wrapper_arguments {TYPE_2__ result; TYPE_1__* args; } ;
typedef  int /*<<< orphan*/  catch_errors_ftype ;
struct TYPE_3__ {struct value* pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ERROR ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ *,struct gdb_wrapper_arguments*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wrap_value_assign ; 

int
gdb_value_assign (struct value *val1, struct value *val2, struct value **result)
{
  struct gdb_wrapper_arguments args;

  args.args[0].pointer = val1;
  args.args[1].pointer = val2;

  if (!catch_errors ((catch_errors_ftype *) wrap_value_assign, &args,
		     "", RETURN_MASK_ERROR))
    {
      /* An error occurred */
      return 0;
    }

  *result = (struct value *) args.result.pointer;
  return 1;
}