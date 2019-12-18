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
 int /*<<< orphan*/  FAIL ; 
 int /*<<< orphan*/ * cur_test_name ; 
 int /*<<< orphan*/  cur_test_outcome ; 
 char* cur_test_prefix ; 
 scalar_t__ opt_verbosity ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  puts (char*) ; 

void
tinytest_set_test_failed_(void)
{
	if (opt_verbosity <= 0 && cur_test_name) {
		if (opt_verbosity==0) puts("");
		printf("%s%s: ", cur_test_prefix, cur_test_name);
		cur_test_name = NULL;
	}
	cur_test_outcome = FAIL;
}