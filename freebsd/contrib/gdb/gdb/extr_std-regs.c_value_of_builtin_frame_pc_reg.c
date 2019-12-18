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
struct frame_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS_TO_POINTER (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ PC_REGNUM ; 
 int /*<<< orphan*/  TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 char* VALUE_CONTENTS_RAW (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct value* allocate_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct value* value_of_register (scalar_t__,struct frame_info*) ; 

__attribute__((used)) static struct value *
value_of_builtin_frame_pc_reg (struct frame_info *frame)
{
  if (PC_REGNUM >= 0)
    return value_of_register (PC_REGNUM, frame);
  else
    {
      struct value *val = allocate_value (builtin_type_void_data_ptr);
      char *buf = VALUE_CONTENTS_RAW (val);
      if (frame == NULL)
	memset (buf, 0, TYPE_LENGTH (VALUE_TYPE (val)));
      else
	ADDRESS_TO_POINTER (builtin_type_void_data_ptr, buf,
			    get_frame_pc (frame));
      return val;
    }
}