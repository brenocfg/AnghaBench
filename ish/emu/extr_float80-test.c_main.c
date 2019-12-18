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
 int /*<<< orphan*/  printf (char*,int,double,double) ; 
 int /*<<< orphan*/  test_compare () ; 
 int /*<<< orphan*/  test_double_convert () ; 
 int /*<<< orphan*/  test_int_convert () ; 
 int /*<<< orphan*/  test_math () ; 
 int tests_passed ; 
 double tests_total ; 

int main() {
    test_int_convert();
    test_double_convert();
    test_math();
    test_compare();
    printf("%d/%d passed (%.0f%%)", tests_passed, tests_total, (double) tests_passed / tests_total * 100);
    return tests_passed == tests_total ? 0 : 1;
}