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
 int /*<<< orphan*/  test_ack_decode ; 
 int /*<<< orphan*/  test_ack_encode ; 
 int /*<<< orphan*/  test_mozquic ; 

void test_frame(void)
{
    subtest("ack-decode", test_ack_decode);
    subtest("ack-encode", test_ack_encode);
    subtest("mozquic", test_mozquic);
}