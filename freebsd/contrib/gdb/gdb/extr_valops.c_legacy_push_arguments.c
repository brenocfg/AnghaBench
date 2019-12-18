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
struct value {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  value_push (int /*<<< orphan*/ ,struct value*) ; 

CORE_ADDR
legacy_push_arguments (int nargs, struct value **args, CORE_ADDR sp,
		       int struct_return, CORE_ADDR struct_addr)
{
  /* ASSERT ( !struct_return); */
  int i;
  for (i = nargs - 1; i >= 0; i--)
    sp = value_push (sp, args[i]);
  return sp;
}