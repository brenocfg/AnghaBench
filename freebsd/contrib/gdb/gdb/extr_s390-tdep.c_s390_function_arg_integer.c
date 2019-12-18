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
 unsigned int TYPE_LENGTH (struct type*) ; 
 scalar_t__ is_integer_like (struct type*) ; 
 scalar_t__ is_pointer_like (struct type*) ; 
 scalar_t__ is_power_of_two (unsigned int) ; 
 scalar_t__ is_struct_like (struct type*) ; 

__attribute__((used)) static int
s390_function_arg_integer (struct type *type)
{
  unsigned length = TYPE_LENGTH (type);
  if (length > 8)
    return 0;

   return is_integer_like (type)
	  || is_pointer_like (type)
	  || (is_struct_like (type) && is_power_of_two (length));
}