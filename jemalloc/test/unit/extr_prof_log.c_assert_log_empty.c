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
 int /*<<< orphan*/  assert_zu_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prof_log_alloc_count () ; 
 int /*<<< orphan*/  prof_log_bt_count () ; 
 int /*<<< orphan*/  prof_log_thr_count () ; 

__attribute__((used)) static void assert_log_empty() {
	assert_zu_eq(prof_log_bt_count(), 0,
	    "The log has backtraces; it isn't empty");
	assert_zu_eq(prof_log_thr_count(), 0,
	    "The log has threads; it isn't empty");
	assert_zu_eq(prof_log_alloc_count(), 0,
	    "The log has allocations; it isn't empty");
}