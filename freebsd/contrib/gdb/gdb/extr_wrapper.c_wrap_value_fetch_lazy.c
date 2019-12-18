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
struct TYPE_2__ {scalar_t__ pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  value_fetch_lazy (struct value*) ; 

__attribute__((used)) static int
wrap_value_fetch_lazy (char *a)
{
  struct gdb_wrapper_arguments *args = (struct gdb_wrapper_arguments *) a;

  value_fetch_lazy ((struct value *) (args)->args[0].pointer);
  return 1;
}