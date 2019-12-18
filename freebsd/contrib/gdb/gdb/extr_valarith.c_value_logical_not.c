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
 int /*<<< orphan*/  COERCE_NUMBER (struct value*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 int TYPE_LENGTH (struct type*) ; 
 char* VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 scalar_t__ value_as_double (struct value*) ; 

int
value_logical_not (struct value *arg1)
{
  int len;
  char *p;
  struct type *type1;

  COERCE_NUMBER (arg1);
  type1 = check_typedef (VALUE_TYPE (arg1));

  if (TYPE_CODE (type1) == TYPE_CODE_FLT)
    return 0 == value_as_double (arg1);

  len = TYPE_LENGTH (type1);
  p = VALUE_CONTENTS (arg1);

  while (--len >= 0)
    {
      if (*p++)
	break;
    }

  return len < 0;
}