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
struct TYPE_4__ {int /*<<< orphan*/  pointer; } ;
struct gdb_wrapper_arguments {TYPE_2__ result; TYPE_1__* args; } ;
struct TYPE_3__ {scalar_t__ pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  value_ind (struct value*) ; 

__attribute__((used)) static int
wrap_value_ind (char *opaque_arg)
{
  struct gdb_wrapper_arguments *args = (struct gdb_wrapper_arguments *) opaque_arg;
  struct value *val;

  val = (struct value *) (args)->args[0].pointer;
  (args)->result.pointer = value_ind (val);
  return 1;
}