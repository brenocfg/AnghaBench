#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct gdb_wrapper_arguments {TYPE_1__* args; } ;
typedef  int /*<<< orphan*/  catch_errors_ftype ;
struct TYPE_2__ {struct value* pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ERROR ; 
 int catch_errors (int /*<<< orphan*/ *,struct gdb_wrapper_arguments*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wrap_value_fetch_lazy ; 

int
gdb_value_fetch_lazy (struct value *value)
{
  struct gdb_wrapper_arguments args;

  args.args[0].pointer = value;
  return catch_errors ((catch_errors_ftype *) wrap_value_fetch_lazy, &args,
		       "", RETURN_MASK_ERROR);
}