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
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_COMPLEX ; 
 scalar_t__ TYPE_CODE_FLT ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 scalar_t__ VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS_RAW (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct value* allocate_value (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  not_lval ; 
 struct value* value_literal_complex (struct value*,struct value*,struct type*) ; 
 struct value* value_zero (struct type*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct value *
cast_into_complex (struct type *type, struct value *val)
{
  struct type *real_type = TYPE_TARGET_TYPE (type);
  if (TYPE_CODE (VALUE_TYPE (val)) == TYPE_CODE_COMPLEX)
    {
      struct type *val_real_type = TYPE_TARGET_TYPE (VALUE_TYPE (val));
      struct value *re_val = allocate_value (val_real_type);
      struct value *im_val = allocate_value (val_real_type);

      memcpy (VALUE_CONTENTS_RAW (re_val),
	      VALUE_CONTENTS (val), TYPE_LENGTH (val_real_type));
      memcpy (VALUE_CONTENTS_RAW (im_val),
	      VALUE_CONTENTS (val) + TYPE_LENGTH (val_real_type),
	      TYPE_LENGTH (val_real_type));

      return value_literal_complex (re_val, im_val, type);
    }
  else if (TYPE_CODE (VALUE_TYPE (val)) == TYPE_CODE_FLT
	   || TYPE_CODE (VALUE_TYPE (val)) == TYPE_CODE_INT)
    return value_literal_complex (val, value_zero (real_type, not_lval), type);
  else
    error ("cannot cast non-number to complex");
}