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
typedef  int test_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  not_reached () ; 
#define  test_status_fail 130 
#define  test_status_pass 129 
#define  test_status_skip 128 

__attribute__((used)) static const char *
test_status_string(test_status_t test_status) {
	switch (test_status) {
	case test_status_pass: return "pass";
	case test_status_skip: return "skip";
	case test_status_fail: return "fail";
	default: not_reached();
	}
}