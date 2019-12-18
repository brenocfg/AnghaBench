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
struct type {int dummy; } ;

/* Variables and functions */
 int TYPE_LENGTH (struct type*) ; 

int
generic_use_struct_convention (int gcc_p, struct type *value_type)
{
  return !((gcc_p == 1)
	   && (TYPE_LENGTH (value_type) == 1
	       || TYPE_LENGTH (value_type) == 2
	       || TYPE_LENGTH (value_type) == 4
	       || TYPE_LENGTH (value_type) == 8));
}