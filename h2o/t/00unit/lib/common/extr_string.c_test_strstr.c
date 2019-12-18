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
 int h2o_strstr (char*,int,char*,int) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_strstr(void)
{
    ok(h2o_strstr("abcd", 4, "bc", 2) == 1);
    ok(h2o_strstr("abcd", 3, "bc", 2) == 1);
    ok(h2o_strstr("abcd", 2, "bc", 2) == -1);
}