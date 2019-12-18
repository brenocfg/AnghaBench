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
struct TYPE_3__ {scalar_t__ pointer; } ;
struct gdb_wrapper_arguments {TYPE_1__ result; TYPE_2__* args; } ;
struct expression {int dummy; } ;
typedef  char* block ;
typedef  int /*<<< orphan*/  catch_errors_ftype ;
struct TYPE_4__ {char** pointer; int integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ERROR ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ *,struct gdb_wrapper_arguments*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wrap_parse_exp_1 ; 

int
gdb_parse_exp_1 (char **stringptr, struct block *block, int comma,
		 struct expression **expression)
{
  struct gdb_wrapper_arguments args;
  args.args[0].pointer = stringptr;
  args.args[1].pointer = block;
  args.args[2].integer = comma;

  if (!catch_errors ((catch_errors_ftype *) wrap_parse_exp_1, &args,
		     "", RETURN_MASK_ERROR))
    {
      /* An error occurred */
      return 0;
    }

  *expression = (struct expression *) args.result.pointer;
  return 1;
  
}