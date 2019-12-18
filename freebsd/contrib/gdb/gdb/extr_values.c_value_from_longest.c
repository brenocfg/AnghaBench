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
typedef  int /*<<< orphan*/  LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_BOOL 135 
#define  TYPE_CODE_CHAR 134 
#define  TYPE_CODE_ENUM 133 
#define  TYPE_CODE_INT 132 
#define  TYPE_CODE_PTR 131 
#define  TYPE_CODE_RANGE 130 
#define  TYPE_CODE_REF 129 
#define  TYPE_CODE_TYPEDEF 128 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS_RAW (struct value*) ; 
 struct value* allocate_value (struct type*) ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  store_signed_integer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_typed_address (int /*<<< orphan*/ ,struct type*,int /*<<< orphan*/ ) ; 

struct value *
value_from_longest (struct type *type, LONGEST num)
{
  struct value *val = allocate_value (type);
  enum type_code code;
  int len;
retry:
  code = TYPE_CODE (type);
  len = TYPE_LENGTH (type);

  switch (code)
    {
    case TYPE_CODE_TYPEDEF:
      type = check_typedef (type);
      goto retry;
    case TYPE_CODE_INT:
    case TYPE_CODE_CHAR:
    case TYPE_CODE_ENUM:
    case TYPE_CODE_BOOL:
    case TYPE_CODE_RANGE:
      store_signed_integer (VALUE_CONTENTS_RAW (val), len, num);
      break;

    case TYPE_CODE_REF:
    case TYPE_CODE_PTR:
      store_typed_address (VALUE_CONTENTS_RAW (val), type, (CORE_ADDR) num);
      break;

    default:
      error ("Unexpected type (%d) encountered for integer constant.", code);
    }
  return val;
}