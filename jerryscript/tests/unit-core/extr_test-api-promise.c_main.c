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
 int /*<<< orphan*/  JERRY_FEATURE_PROMISE ; 
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  JERRY_LOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_is_feature_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_port_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_promise_from_js () ; 
 int /*<<< orphan*/  test_promise_resolve_fail () ; 
 int /*<<< orphan*/  test_promise_resolve_success () ; 

int
main (void)
{
  if (!jerry_is_feature_enabled (JERRY_FEATURE_PROMISE))
  {
    jerry_port_log (JERRY_LOG_LEVEL_ERROR, "Promise is disabled!\n");
    return 0;
  }

  jerry_init (JERRY_INIT_EMPTY);

  test_promise_resolve_fail ();
  test_promise_resolve_success ();

  test_promise_from_js ();

  jerry_cleanup ();

  return 0;
}