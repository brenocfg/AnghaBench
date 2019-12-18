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
 int /*<<< orphan*/  JERRY_INIT_EMPTY ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  jerry_cleanup () ; 
 int /*<<< orphan*/ * jerry_get_context_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jerry_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager1 ; 
 int /*<<< orphan*/  manager2 ; 
 int /*<<< orphan*/  manager3 ; 
 int /*<<< orphan*/  manager4 ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int test_context_data1_finalize_called ; 
 int test_context_data1_free_called ; 
 int test_context_data1_new_called ; 
 int test_context_data2_free_called ; 
 int test_context_data2_new_called ; 
 int test_context_data3_new_called ; 
 int test_context_data4_finalize_called ; 
 int test_context_data4_free_called ; 
 int test_context_data4_new_called ; 

int
main (void)
{
  TEST_INIT ();

  jerry_init (JERRY_INIT_EMPTY);

  TEST_ASSERT (!strcmp (*((const char **) jerry_get_context_data (&manager1)), "item1"));
  TEST_ASSERT (!strcmp (*((const char **) jerry_get_context_data (&manager2)), "item2"));
  TEST_ASSERT (jerry_get_context_data (&manager3) == NULL);
  TEST_ASSERT (jerry_get_context_data (&manager4) == NULL);

  TEST_ASSERT (test_context_data1_new_called);
  TEST_ASSERT (test_context_data2_new_called);
  TEST_ASSERT (test_context_data3_new_called);
  TEST_ASSERT (test_context_data4_new_called);

  TEST_ASSERT (!test_context_data1_free_called);
  TEST_ASSERT (!test_context_data2_free_called);
  TEST_ASSERT (!test_context_data4_free_called);

  jerry_cleanup ();

  TEST_ASSERT (test_context_data1_free_called);
  TEST_ASSERT (test_context_data2_free_called);
  TEST_ASSERT (test_context_data4_free_called);

  TEST_ASSERT (test_context_data1_finalize_called);
  TEST_ASSERT (test_context_data4_finalize_called);

  return 0;
}