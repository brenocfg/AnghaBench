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
typedef  scalar_t__ jerryx_handle_scope ;
typedef  int /*<<< orphan*/  jerry_value_t ;

/* Variables and functions */
 int JERRYX_SCOPE_PRELIST_SIZE ; 
 int /*<<< orphan*/  JERRY_GC_PRESSURE_LOW ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  create_object_nested (int) ; 
 int /*<<< orphan*/  jerry_gc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_close_handle_scope (scalar_t__) ; 
 scalar_t__ jerryx_handle_scope_get_current () ; 
 int /*<<< orphan*/  jerryx_open_handle_scope (scalar_t__*) ; 
 scalar_t__ native_free_cb_call_count ; 

__attribute__((used)) static void
test_handle_scope_val (void)
{
  jerryx_handle_scope scope;
  jerryx_open_handle_scope (&scope);

  for (int idx = 0; idx < 2; ++idx)
  {
    jerry_value_t obj = create_object_nested (JERRYX_SCOPE_PRELIST_SIZE * 2);
    (void) obj;
  }

  TEST_ASSERT (jerryx_handle_scope_get_current () == scope);

  jerry_gc (JERRY_GC_PRESSURE_LOW);
  TEST_ASSERT (native_free_cb_call_count == 0);

  jerryx_close_handle_scope (scope);
}