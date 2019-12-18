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
 int /*<<< orphan*/  ATF_REQUIRE_EQ (double,int) ; 
 int N_RECURSE ; 
 int /*<<< orphan*/  PTHREAD_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_pass () ; 
 int mul3 (int,int,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recurse () ; 
 int /*<<< orphan*/  recursion_depth ; 
 int /*<<< orphan*/  recursion_depth_lock ; 

__attribute__((used)) static void *
bar(void *p)
{
	double d;
	int rc;

	d = mul3(mul3(2., 3., 5.), mul3(7., 11., 13.), mul3(17., 19., 23.));
	ATF_REQUIRE_EQ(d, 223092870.);

	PTHREAD_REQUIRE(pthread_mutex_lock(&recursion_depth_lock));
	rc = recursion_depth++;
	PTHREAD_REQUIRE(pthread_mutex_unlock(&recursion_depth_lock));

	if (rc < N_RECURSE)
		recurse();
	else
		atf_tc_pass();

	/* NOTREACHED */
	return NULL;
}