#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const* const* const* const* jerry_value_t ;
typedef  int /*<<< orphan*/  const* const* const* const* const* jerry_length_t ;
struct TYPE_3__ {int x; } ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_UNUSED (int /*<<< orphan*/  const* const* const* const* const* const) ; 
 int /*<<< orphan*/  TEST_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* const* const* const* jerry_create_boolean (int) ; 
 int /*<<< orphan*/  jerry_set_object_native_pointer (int /*<<< orphan*/  const* const* const* const* const,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerry_value_is_object (int /*<<< orphan*/  const* const* const* const* const) ; 
 TYPE_1__ my_thing_a ; 
 int /*<<< orphan*/  thing_a_info ; 

__attribute__((used)) static jerry_value_t
create_object_a_handler (const jerry_value_t func_obj_val, /**< function object */
                         const jerry_value_t this_val, /**< this value */
                         const jerry_value_t args_p[], /**< arguments list */
                         const jerry_length_t args_cnt) /**< arguments length */
{
  JERRY_UNUSED (func_obj_val);
  JERRY_UNUSED (args_p);
  JERRY_UNUSED (args_cnt);

  TEST_ASSERT (jerry_value_is_object (this_val));

  my_thing_a.x = 1;
  jerry_set_object_native_pointer (this_val,
                                   &my_thing_a,
                                   &thing_a_info);

  return jerry_create_boolean (true);
}