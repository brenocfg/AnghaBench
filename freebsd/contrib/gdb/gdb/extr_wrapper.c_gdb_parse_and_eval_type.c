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
struct type {int dummy; } ;
struct TYPE_4__ {scalar_t__ pointer; } ;
struct gdb_wrapper_arguments {TYPE_2__ result; TYPE_1__* args; } ;
typedef  int /*<<< orphan*/  catch_errors_ftype ;
struct TYPE_3__ {char* pointer; int integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ *,struct gdb_wrapper_arguments*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wrap_parse_and_eval_type ; 

int
gdb_parse_and_eval_type (char *p, int length, struct type **type)
{
  struct gdb_wrapper_arguments args;
  args.args[0].pointer = p;
  args.args[1].integer = length;

  if (!catch_errors ((catch_errors_ftype *) wrap_parse_and_eval_type, &args,
		     "", RETURN_MASK_ALL))
    {
      /* An error occurred */
      return 0;
    }

  *type = (struct type *) args.result.pointer;
  return 1;
}