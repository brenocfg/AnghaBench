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
 int /*<<< orphan*/  test_change_weight ; 
 int /*<<< orphan*/  test_dependency ; 
 int /*<<< orphan*/  test_exclusive ; 
 int /*<<< orphan*/  test_exclusive_at_current_pos ; 
 int /*<<< orphan*/  test_firefox ; 
 int /*<<< orphan*/  test_priority ; 
 int /*<<< orphan*/  test_queue ; 
 int /*<<< orphan*/  test_reprioritize ; 
 int test_reprioritize_exclusive ; 
 int /*<<< orphan*/  test_round_robin ; 

void test_lib__http2__scheduler(void)
{
    subtest("drr", test_queue);
    subtest("round-robin", test_round_robin);
    subtest("priority", test_priority);
    subtest("dependency", test_dependency);
    subtest("exclusive", test_exclusive);
    subtest("firefox", test_firefox);
    test_reprioritize_exclusive = 0;
    subtest("repriortize-nonexclusive", test_reprioritize);
    test_reprioritize_exclusive = 1;
    subtest("repriortize-exclusive", test_reprioritize);
    subtest("change-weight", test_change_weight);
    subtest("exclusive-at-current-pos", test_exclusive_at_current_pos);
}