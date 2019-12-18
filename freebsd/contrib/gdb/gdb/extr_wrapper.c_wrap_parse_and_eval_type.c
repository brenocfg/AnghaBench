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
struct TYPE_4__ {char* pointer; } ;
struct gdb_wrapper_arguments {TYPE_2__ result; TYPE_1__* args; } ;
struct TYPE_3__ {int integer; scalar_t__ pointer; } ;

/* Variables and functions */
 scalar_t__ parse_and_eval_type (char*,int) ; 

__attribute__((used)) static int
wrap_parse_and_eval_type (char *a)
{
  struct gdb_wrapper_arguments *args = (struct gdb_wrapper_arguments *) a;

  char *p = (char *) args->args[0].pointer;
  int length = args->args[1].integer;

  args->result.pointer = (char *) parse_and_eval_type (p, length);

  return 1;
}