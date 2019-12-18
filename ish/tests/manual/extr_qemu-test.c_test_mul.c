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
 int /*<<< orphan*/  TEST_IMUL_IM (char*,char*,int,int) ; 
 int /*<<< orphan*/  test_divb (int,int) ; 
 int /*<<< orphan*/  test_divl (int,int,int) ; 
 int /*<<< orphan*/  test_divq (int,int,int) ; 
 int /*<<< orphan*/  test_divw (int,int,int) ; 
 int /*<<< orphan*/  test_idivb (int,int) ; 
 int /*<<< orphan*/  test_idivl (int,int,int) ; 
 int /*<<< orphan*/  test_idivq (int,int,int) ; 
 int /*<<< orphan*/  test_idivw (int,int,int) ; 
 int /*<<< orphan*/  test_imulb (int,int) ; 
 int /*<<< orphan*/  test_imull (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_imull2 (int,int) ; 
 int /*<<< orphan*/  test_imulq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_imulq2 (int,int) ; 
 int /*<<< orphan*/  test_imulw (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_imulw2 (int,int) ; 
 int /*<<< orphan*/  test_mulb (int,int) ; 
 int /*<<< orphan*/  test_mull (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_mulq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_mulw (int /*<<< orphan*/ ,int,int) ; 

void test_mul(void)
{
    test_imulb(0x1234561d, 4);
    test_imulb(3, -4);
    test_imulb(0x80, 0x80);
    test_imulb(0x10, 0x10);

    test_imulw(0, 0x1234001d, 45);
    test_imulw(0, 23, -45);
    test_imulw(0, 0x8000, 0x8000);
    test_imulw(0, 0x100, 0x100);

    test_imull(0, 0x1234001d, 45);
    test_imull(0, 23, -45);
    test_imull(0, 0x80000000, 0x80000000);
    test_imull(0, 0x10000, 0x10000);

    test_mulb(0x1234561d, 4);
    test_mulb(3, -4);
    test_mulb(0x80, 0x80);
    test_mulb(0x10, 0x10);

    test_mulw(0, 0x1234001d, 45);
    test_mulw(0, 23, -45);
    test_mulw(0, 0x8000, 0x8000);
    test_mulw(0, 0x100, 0x100);

    test_mull(0, 0x1234001d, 45);
    test_mull(0, 23, -45);
    test_mull(0, 0x80000000, 0x80000000);
    test_mull(0, 0x10000, 0x10000);

    test_imulw2(0x1234001d, 45);
    test_imulw2(23, -45);
    test_imulw2(0x8000, 0x8000);
    test_imulw2(0x100, 0x100);

    test_imull2(0x1234001d, 45);
    test_imull2(23, -45);
    test_imull2(0x80000000, 0x80000000);
    test_imull2(0x10000, 0x10000);

    TEST_IMUL_IM("w", "w", 45, 0x1234);
    TEST_IMUL_IM("w", "w", -45, 23);
    TEST_IMUL_IM("w", "w", 0x8000, 0x80000000);
    TEST_IMUL_IM("w", "w", 0x7fff, 0x1000);

    TEST_IMUL_IM("l", "k", 45, 0x1234);
    TEST_IMUL_IM("l", "k", -45, 23);
    TEST_IMUL_IM("l", "k", 0x8000, 0x80000000);
    TEST_IMUL_IM("l", "k", 0x7fff, 0x1000);

    test_idivb(0x12341678, 0x127e);
    test_idivb(0x43210123, -5);
    test_idivb(0x12340004, -1);

    test_idivw(0, 0x12345678, 12347);
    test_idivw(0, -23223, -45);
    test_idivw(0, 0x12348000, -1);
    test_idivw(0x12343, 0x12345678, 0x81238567);

    test_idivl(0, 0x12345678, 12347);
    test_idivl(0, -233223, -45);
    test_idivl(0, 0x80000000, -1);
    test_idivl(0x12343, 0x12345678, 0x81234567);

    test_divb(0x12341678, 0x127e);
    test_divb(0x43210123, -5);
    test_divb(0x12340004, -1);

    test_divw(0, 0x12345678, 12347);
    test_divw(0, -23223, -45);
    test_divw(0, 0x12348000, -1);
    test_divw(0x12343, 0x12345678, 0x81238567);

    test_divl(0, 0x12345678, 12347);
    test_divl(0, -233223, -45);
    test_divl(0, 0x80000000, -1);
    test_divl(0x12343, 0x12345678, 0x81234567);

#if defined(__x86_64__)
    test_imulq(0, 0x1234001d1234001d, 45);
    test_imulq(0, 23, -45);
    test_imulq(0, 0x8000000000000000, 0x8000000000000000);
    test_imulq(0, 0x100000000, 0x100000000);

    test_mulq(0, 0x1234001d1234001d, 45);
    test_mulq(0, 23, -45);
    test_mulq(0, 0x8000000000000000, 0x8000000000000000);
    test_mulq(0, 0x100000000, 0x100000000);

    test_imulq2(0x1234001d1234001d, 45);
    test_imulq2(23, -45);
    test_imulq2(0x8000000000000000, 0x8000000000000000);
    test_imulq2(0x100000000, 0x100000000);

    TEST_IMUL_IM("q", "", 45, 0x12341234);
    TEST_IMUL_IM("q", "", -45, 23);
    TEST_IMUL_IM("q", "", 0x8000, 0x8000000000000000);
    TEST_IMUL_IM("q", "", 0x7fff, 0x10000000);

    test_idivq(0, 0x12345678abcdef, 12347);
    test_idivq(0, -233223, -45);
    test_idivq(0, 0x8000000000000000, -1);
    test_idivq(0x12343, 0x12345678, 0x81234567);

    test_divq(0, 0x12345678abcdef, 12347);
    test_divq(0, -233223, -45);
    test_divq(0, 0x8000000000000000, -1);
    test_divq(0x12343, 0x12345678, 0x81234567);
#endif
}