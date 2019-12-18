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
struct TYPE_3__ {int /*<<< orphan*/  pointer; } ;
struct gdb_wrapper_arguments {TYPE_2__* args; TYPE_1__ result; } ;
struct block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  integer; scalar_t__ pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  parse_exp_1 (char**,struct block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
wrap_parse_exp_1 (char *argptr)
{
  struct gdb_wrapper_arguments *args 
    = (struct gdb_wrapper_arguments *) argptr;
  args->result.pointer = parse_exp_1((char **) args->args[0].pointer,
				     (struct block *) args->args[1].pointer,
				     args->args[2].integer);
  return 1;
}