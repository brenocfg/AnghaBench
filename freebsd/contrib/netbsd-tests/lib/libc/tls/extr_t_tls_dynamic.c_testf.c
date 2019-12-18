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
 int /*<<< orphan*/  ATF_CHECK_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dso_var1 ; 
 int /*<<< orphan*/ * getpid ; 
 int /*<<< orphan*/  optind ; 
 int /*<<< orphan*/  testf_dso_helper (int,int) ; 
 int /*<<< orphan*/  var1 ; 
 int /*<<< orphan*/  var2 ; 
 int /*<<< orphan*/  var3 ; 
 int /*<<< orphan*/  var4 ; 
 int /*<<< orphan*/  var4_helper ; 

__attribute__((used)) static void *
testf(void *dummy)
{
	ATF_CHECK_EQ(var1, 1);
	ATF_CHECK_EQ(var2, 0);
	testf_dso_helper(2, 2);
	ATF_CHECK_EQ(var1, 2);
	ATF_CHECK_EQ(var2, 2);
	testf_dso_helper(3, 3);
	ATF_CHECK_EQ(var1, 3);
	ATF_CHECK_EQ(var2, 3);
	ATF_CHECK_EQ(var3, &optind);
	ATF_CHECK_EQ(var4, &var4_helper);
	ATF_CHECK_EQ(dso_var1, getpid);

	return NULL;
}