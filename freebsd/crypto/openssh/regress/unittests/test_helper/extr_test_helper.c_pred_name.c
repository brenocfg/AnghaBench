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
typedef  enum test_predicate { ____Placeholder_test_predicate } test_predicate ;

/* Variables and functions */
#define  TEST_EQ 133 
#define  TEST_GE 132 
#define  TEST_GT 131 
#define  TEST_LE 130 
#define  TEST_LT 129 
#define  TEST_NE 128 

__attribute__((used)) static const char *
pred_name(enum test_predicate p)
{
	switch (p) {
	case TEST_EQ:
		return "EQ";
	case TEST_NE:
		return "NE";
	case TEST_LT:
		return "LT";
	case TEST_LE:
		return "LE";
	case TEST_GT:
		return "GT";
	case TEST_GE:
		return "GE";
	default:
		return "UNKNOWN";
	}
}