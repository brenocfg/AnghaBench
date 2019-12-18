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
 int /*<<< orphan*/  test_hostport ; 
 int /*<<< orphan*/  test_normalize_path ; 
 int /*<<< orphan*/  test_parse ; 
 int /*<<< orphan*/  test_parse_relative ; 
 int /*<<< orphan*/  test_resolve ; 

void test_lib__common__url_c(void)
{
    subtest("normalize_path", test_normalize_path);
    subtest("hostport", test_hostport);
    subtest("parse", test_parse);
    subtest("parse_relative", test_parse_relative);
    subtest("resolve", test_resolve);
}