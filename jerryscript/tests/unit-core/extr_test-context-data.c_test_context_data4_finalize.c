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
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int test_context_data4_finalize_called ; 

__attribute__((used)) static void
test_context_data4_finalize (void *user_data_p)
{
  TEST_ASSERT (!test_context_data4_finalize_called);
  test_context_data4_finalize_called = true;
  TEST_ASSERT (user_data_p == NULL);
}