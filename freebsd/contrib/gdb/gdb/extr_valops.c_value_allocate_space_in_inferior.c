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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_OF_MALLOC ; 
 int /*<<< orphan*/  builtin_type_int ; 
 struct value* call_function_by_hand (struct value*,int,struct value**) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct value* find_function_in_inferior (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_has_execution ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ value_logical_not (struct value*) ; 

struct value *
value_allocate_space_in_inferior (int len)
{
  struct value *blocklen;
  struct value *val = find_function_in_inferior (NAME_OF_MALLOC);

  blocklen = value_from_longest (builtin_type_int, (LONGEST) len);
  val = call_function_by_hand (val, 1, &blocklen);
  if (value_logical_not (val))
    {
      if (!target_has_execution)
	error ("No memory available to program now: you need to start the target first");
      else
	error ("No memory available to program: call to malloc failed");
    }
  return val;
}