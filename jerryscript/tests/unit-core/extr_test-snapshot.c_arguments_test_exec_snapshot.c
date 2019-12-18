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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  jerry_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_exec_snapshot (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double jerry_get_number_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_release_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_value_is_error (int /*<<< orphan*/ ) ; 
 int jerry_value_is_number (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arguments_test_exec_snapshot (uint32_t *snapshot_p, size_t snapshot_size, uint32_t exec_snapshot_flags)
{
  jerry_init (JERRY_INIT_EMPTY);
  jerry_value_t res = jerry_exec_snapshot (snapshot_p, snapshot_size, 0, exec_snapshot_flags);
  TEST_ASSERT (!jerry_value_is_error (res));
  TEST_ASSERT (jerry_value_is_number (res));
  double raw_value = jerry_get_number_value (res);
  TEST_ASSERT (raw_value == 15);
  jerry_release_value (res);

  jerry_cleanup ();
}