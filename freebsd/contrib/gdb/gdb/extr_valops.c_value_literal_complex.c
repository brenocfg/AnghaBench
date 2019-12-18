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
 scalar_t__ TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 scalar_t__ VALUE_CONTENTS_RAW (struct value*) ; 
 struct value* allocate_value (struct type*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct value* value_cast (struct type*,struct value*) ; 

struct value *
value_literal_complex (struct value *arg1, struct value *arg2, struct type *type)
{
  struct value *val;
  struct type *real_type = TYPE_TARGET_TYPE (type);

  val = allocate_value (type);
  arg1 = value_cast (real_type, arg1);
  arg2 = value_cast (real_type, arg2);

  memcpy (VALUE_CONTENTS_RAW (val),
	  VALUE_CONTENTS (arg1), TYPE_LENGTH (real_type));
  memcpy (VALUE_CONTENTS_RAW (val) + TYPE_LENGTH (real_type),
	  VALUE_CONTENTS (arg2), TYPE_LENGTH (real_type));
  return val;
}