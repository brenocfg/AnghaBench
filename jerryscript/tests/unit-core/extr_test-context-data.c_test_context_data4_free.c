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
 int /*<<< orphan*/  test_context_data4_finalize_called ; 
 int test_context_data4_free_called ; 

__attribute__((used)) static void
test_context_data4_free (void *user_data_p)
{
  test_context_data4_free_called = true;
  TEST_ASSERT (user_data_p == NULL);
  TEST_ASSERT (!test_context_data4_finalize_called);
}