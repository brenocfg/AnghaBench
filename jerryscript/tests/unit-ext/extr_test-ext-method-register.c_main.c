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
 int /*<<< orphan*/  test_error_multiple_functions () ; 
 int /*<<< orphan*/  test_error_setvalue () ; 
 int /*<<< orphan*/  test_error_single_function () ; 
 int /*<<< orphan*/  test_simple_registration () ; 

int
main (void)
{
  test_simple_registration ();
  test_error_setvalue ();
  test_error_single_function ();
  test_error_multiple_functions ();
  return 0;
}