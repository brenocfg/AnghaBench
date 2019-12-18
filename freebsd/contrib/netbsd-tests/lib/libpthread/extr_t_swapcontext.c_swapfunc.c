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
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nctx ; 
 void* nself ; 
 int /*<<< orphan*/  octx ; 
 int /*<<< orphan*/  oself ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ pthread_self () ; 
 int /*<<< orphan*/  swapcontext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
swapfunc(void *arg)
{
	/*
	 * If the test fails, we are very likely to crash 
	 * without the opportunity to report
	 */ 
	nself = (void *)pthread_self();
	printf("after swapcontext self = %p\n", nself);

	ATF_REQUIRE_EQ(oself, nself);
	printf("Test succeeded\n");
	/* Go back in main */
	ATF_REQUIRE(swapcontext(&nctx, &octx));

	/* NOTREACHED */
	return;
}