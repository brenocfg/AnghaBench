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
 int /*<<< orphan*/  TEST_BSX (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bsfl ; 
 int /*<<< orphan*/  bsfq ; 
 int /*<<< orphan*/  bsfw ; 
 int /*<<< orphan*/  bsrl ; 
 int /*<<< orphan*/  bsrq ; 
 int /*<<< orphan*/  bsrw ; 

void test_bsx(void)
{
    TEST_BSX(bsrw, "w", 0);
    TEST_BSX(bsrw, "w", 0x12340128);
    TEST_BSX(bsfw, "w", 0);
    TEST_BSX(bsfw, "w", 0x12340128);
    TEST_BSX(bsrl, "k", 0);
    TEST_BSX(bsrl, "k", 0x00340128);
    TEST_BSX(bsfl, "k", 0);
    TEST_BSX(bsfl, "k", 0x00340128);
#if defined(__x86_64__)
    TEST_BSX(bsrq, "", 0);
    TEST_BSX(bsrq, "", 0x003401281234);
    TEST_BSX(bsfq, "", 0);
    TEST_BSX(bsfq, "", 0x003401281234);
#endif
}