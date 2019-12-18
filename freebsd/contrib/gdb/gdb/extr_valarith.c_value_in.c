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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LA_BOOL_TYPE ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_BOOL ; 
 scalar_t__ TYPE_CODE_CHAR ; 
 scalar_t__ TYPE_CODE_ENUM ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_CODE_RANGE ; 
 scalar_t__ TYPE_CODE_SET ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  value_as_long (struct value*) ; 
 int value_bit_index (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,int) ; 

struct value *
value_in (struct value *element, struct value *set)
{
  int member;
  struct type *settype = check_typedef (VALUE_TYPE (set));
  struct type *eltype = check_typedef (VALUE_TYPE (element));
  if (TYPE_CODE (eltype) == TYPE_CODE_RANGE)
    eltype = TYPE_TARGET_TYPE (eltype);
  if (TYPE_CODE (settype) != TYPE_CODE_SET)
    error ("Second argument of 'IN' has wrong type");
  if (TYPE_CODE (eltype) != TYPE_CODE_INT
      && TYPE_CODE (eltype) != TYPE_CODE_CHAR
      && TYPE_CODE (eltype) != TYPE_CODE_ENUM
      && TYPE_CODE (eltype) != TYPE_CODE_BOOL)
    error ("First argument of 'IN' has wrong type");
  member = value_bit_index (settype, VALUE_CONTENTS (set),
			    value_as_long (element));
  if (member < 0)
    error ("First argument of 'IN' not in range");
  return value_from_longest (LA_BOOL_TYPE, member);
}