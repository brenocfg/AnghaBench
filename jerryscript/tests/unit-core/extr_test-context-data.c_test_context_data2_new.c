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
 char* string2 ; 
 int test_context_data2_new_called ; 

__attribute__((used)) static void
test_context_data2_new (void *user_data_p)
{
  test_context_data2_new_called = true;
  *((const char **) user_data_p) = string2;
}