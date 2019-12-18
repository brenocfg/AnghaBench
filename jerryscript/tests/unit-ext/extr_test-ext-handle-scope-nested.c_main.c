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

/* Variables and functions */
 int /*<<< orphan*/  JERRY_GC_PRESSURE_LOW ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_gc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int native_free_cb_call_count ; 
 int /*<<< orphan*/  test_handle_scope_val () ; 

int
main (void)
{
  jerry_init (JERRY_INIT_EMPTY);

  native_free_cb_call_count = 0;
  test_handle_scope_val ();

  jerry_gc (JERRY_GC_PRESSURE_LOW);
  TEST_ASSERT (native_free_cb_call_count == 2);

  jerry_cleanup ();
}