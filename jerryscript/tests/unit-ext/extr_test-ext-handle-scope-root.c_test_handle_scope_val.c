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
typedef  int /*<<< orphan*/  jerryx_escapable_handle_scope ;
typedef  int /*<<< orphan*/  jerry_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_GC_PRESSURE_LOW ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  create_object () ; 
 int /*<<< orphan*/  jerry_gc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_close_handle_scope (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_create_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerryx_handle_scope_get_root () ; 
 int native_free_cb_call_count ; 
 int reusing_times ; 

__attribute__((used)) static void
test_handle_scope_val (void)
{
  jerryx_escapable_handle_scope root = jerryx_handle_scope_get_root ();
  // root handle scope should always be reusable after close
  for (int i = 0; i < reusing_times; ++i)
  {
    jerry_value_t obj = jerryx_create_handle (create_object ());
    (void) obj;
    jerryx_close_handle_scope (root);
    jerry_gc (JERRY_GC_PRESSURE_LOW);
    TEST_ASSERT (native_free_cb_call_count == (i + 1));
  }
}