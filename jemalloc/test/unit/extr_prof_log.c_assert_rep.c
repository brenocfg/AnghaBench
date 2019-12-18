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
 int /*<<< orphan*/  assert_b_eq (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  prof_log_rep_check () ; 

__attribute__((used)) static void assert_rep() {
	assert_b_eq(prof_log_rep_check(), false, "Rep check failed");
}