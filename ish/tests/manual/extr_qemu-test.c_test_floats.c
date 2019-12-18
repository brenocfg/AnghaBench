#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int d; } ;

/* Variables and functions */
 scalar_t__ TEST_CMOV ; 
 TYPE_1__ q_nan ; 
 int /*<<< orphan*/  test_fbcd (double) ; 
 int /*<<< orphan*/  test_fcmov () ; 
 int /*<<< orphan*/  test_fcmp (double,int) ; 
 int /*<<< orphan*/  test_fconst () ; 
 int /*<<< orphan*/  test_fcvt (double) ; 
 int /*<<< orphan*/  test_fenv () ; 
 int /*<<< orphan*/  test_fops (double,int) ; 

void test_floats(void)
{
    test_fops(2, 3);
    test_fops(1.4, -5);
    test_fcmp(2, -1);
    test_fcmp(2, 2);
    test_fcmp(2, 3);
    test_fcmp(2, q_nan.d);
    test_fcmp(q_nan.d, -1);
    test_fcmp(-1.0/0.0, -1);
    test_fcmp(1.0/0.0, -1);
    test_fcvt(0.5);
    test_fcvt(-0.5);
    test_fcvt(1.0/7.0);
    test_fcvt(-1.0/9.0);
    test_fcvt(32768);
    test_fcvt(-1e20);
    test_fcvt(-1.0/0.0);
    test_fcvt(1.0/0.0);
    test_fcvt(q_nan.d);
    test_fconst();
    test_fbcd(1234567890123456.0);
    test_fbcd(-123451234567890.0);
    test_fenv();
    if (TEST_CMOV) {
        test_fcmov();
    }
}