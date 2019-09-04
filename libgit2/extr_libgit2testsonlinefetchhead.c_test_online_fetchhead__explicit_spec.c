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
 int /*<<< orphan*/  FETCH_HEAD_EXPLICIT_DATA ; 
 int /*<<< orphan*/  fetchhead_test_clone () ; 
 int /*<<< orphan*/  fetchhead_test_fetch (char*,int /*<<< orphan*/ ) ; 

void test_online_fetchhead__explicit_spec(void)
{
	fetchhead_test_clone();
	fetchhead_test_fetch("refs/heads/first-merge:refs/remotes/origin/first-merge", FETCH_HEAD_EXPLICIT_DATA);
}