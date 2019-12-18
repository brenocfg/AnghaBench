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
 int /*<<< orphan*/  printf (char*) ; 
 int test_api_is_free_callback_was_called ; 

__attribute__((used)) static void
handler_construct_2_freecb (void *native_p)
{
  TEST_ASSERT ((uintptr_t) native_p == (uintptr_t) 0x0012345678abcdefull);
  printf ("ok object free callback\n");

  test_api_is_free_callback_was_called = true;
}