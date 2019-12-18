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
typedef  enum type_code { ____Placeholder_type_code } type_code ;
typedef  int /*<<< orphan*/  DOUBLEST ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_FLT ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS_RAW (struct value*) ; 
 struct value* allocate_value (struct type*) ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  store_typed_floating (int /*<<< orphan*/ ,struct type*,int /*<<< orphan*/ ) ; 

struct value *
value_from_double (struct type *type, DOUBLEST num)
{
  struct value *val = allocate_value (type);
  struct type *base_type = check_typedef (type);
  enum type_code code = TYPE_CODE (base_type);
  int len = TYPE_LENGTH (base_type);

  if (code == TYPE_CODE_FLT)
    {
      store_typed_floating (VALUE_CONTENTS_RAW (val), base_type, num);
    }
  else
    error ("Unexpected type encountered for floating constant.");

  return val;
}