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
 int /*<<< orphan*/  subtest (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_calc_key ; 
 int /*<<< orphan*/  test_cookie ; 
 int /*<<< orphan*/  test_cookie_merge ; 
 int /*<<< orphan*/  test_lookup ; 

void test_lib__http2__casper(void)
{
    subtest("calc_key", test_calc_key);
    subtest("test_lookup", test_lookup);
    subtest("cookie", test_cookie);
    subtest("cookie-merge", test_cookie_merge);
}