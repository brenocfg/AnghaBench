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
 int /*<<< orphan*/  assert_has_reflog (int,char*) ; 

void test_refs_reflog_reflog__reference_has_reflog(void)
{
	assert_has_reflog(true, "HEAD");
	assert_has_reflog(true, "refs/heads/master");
	assert_has_reflog(false, "refs/heads/subtrees");
}