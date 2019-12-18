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
 int /*<<< orphan*/  JERRY_FEATURE_LINE_INFO ; 
 int /*<<< orphan*/  TEST_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  jerry_is_feature_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_exception_backtrace () ; 
 int /*<<< orphan*/  test_get_backtrace_api_call () ; 
 int /*<<< orphan*/  test_large_line_count () ; 

int
main (void)
{
  TEST_INIT ();

  TEST_ASSERT (jerry_is_feature_enabled (JERRY_FEATURE_LINE_INFO));

  test_get_backtrace_api_call ();
  test_exception_backtrace ();
  test_large_line_count ();

  return 0;
}