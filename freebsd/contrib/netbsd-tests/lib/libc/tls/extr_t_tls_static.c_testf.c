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
 int /*<<< orphan*/  testf_helper () ; 
 int /*<<< orphan*/  var1 ; 
 int /*<<< orphan*/  var2 ; 

__attribute__((used)) static void *
testf(void *dummy)
{
	ATF_CHECK_EQ(var1, 1);
	ATF_CHECK_EQ(var2, 0);
	testf_helper();
	ATF_CHECK_EQ(var1, -1);
	ATF_CHECK_EQ(var2, -1);

	return NULL;
}