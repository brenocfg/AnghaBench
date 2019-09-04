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
 int /*<<< orphan*/  ID_BRANCH_A ; 
 int /*<<< orphan*/  ID_BRANCH_B ; 
 int /*<<< orphan*/  SRC_REPO ; 
 int /*<<< orphan*/  perf__do_merge (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_perf_merge__m1(void)
{
	perf__do_merge(SRC_REPO, "m1", ID_BRANCH_A, ID_BRANCH_B);
}