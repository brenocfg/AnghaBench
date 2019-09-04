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
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int h2o_str_at_position (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ok (int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void test_at_position(void)
{
    char buf[160];
    int ret;

    /* normal cases */
    ret = h2o_str_at_position(buf, H2O_STRLIT("hello\nworld\n"), 1, 1);
    ok(ret == 0);
    ok(strcmp(buf, "hello\n^\n") == 0);

    ret = h2o_str_at_position(buf, H2O_STRLIT("hello\nworld\n"), 1, 5);
    ok(ret == 0);
    ok(strcmp(buf, "hello\n    ^\n") == 0);

    ret = h2o_str_at_position(buf, H2O_STRLIT("hello\nworld\n"), 1, 6);
    ok(ret == 0);
    ok(strcmp(buf, "hello\n     ^\n") == 0);

    ret = h2o_str_at_position(buf, H2O_STRLIT("hello\nworld\n"), 1, 7);
    ok(ret == 0);
    ok(strcmp(buf, "hello\n     ^\n") == 0);

    ret = h2o_str_at_position(buf, H2O_STRLIT("hello\nworld\n"), 2, 1);
    ok(ret == 0);
    ok(strcmp(buf, "world\n^\n") == 0);

    ret = h2o_str_at_position(buf, H2O_STRLIT("hello\nworld\n"), 2, 5);
    ok(ret == 0);
    ok(strcmp(buf, "world\n    ^\n") == 0);

    ret = h2o_str_at_position(buf, H2O_STRLIT("hello\nworld\n"), 1, 7);
    ok(ret == 0);
    ok(strcmp(buf, "hello\n     ^\n") == 0);

    ret = h2o_str_at_position(
        buf, H2O_STRLIT("_________1_________2_________3_________4_________5_________6_________7_________\nworld\n"), 1, 5);
    ok(ret == 0);
    ok(strcmp(buf, "_________1_________2_________3_________4_________5_________6_________7______\n    ^\n") == 0);

    ret = h2o_str_at_position(
        buf, H2O_STRLIT("_________1_________2_________3_________4_________5_________6_________7_________\nworld\n"), 1, 60);
    ok(ret == 0);
    ok(strcmp(buf, "_________3_________4_________5_________6_________7_________\n                                       ^\n") == 0);

    ret = h2o_str_at_position(buf, H2O_STRLIT("hello"), 1, 20);
    ok(ret == 0);
    ok(strcmp(buf, "hello\n     ^\n") == 0);

    /* error cases */
    ret = h2o_str_at_position(buf, H2O_STRLIT("hello\nworld\n"), 0, 1);
    ok(ret != 0);

    ret = h2o_str_at_position(buf, H2O_STRLIT("hello\nworld\n"), 1, 0);
    ok(ret != 0);

    ret = h2o_str_at_position(buf, H2O_STRLIT("hello\nworld\n"), 4, 1);
    ok(ret != 0);
}