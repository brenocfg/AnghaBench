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
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int,int) ; 
 int /*<<< orphan*/  PTHREAD_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  once ; 
 int /*<<< orphan*/  once2_ofunc ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int x ; 

__attribute__((used)) static void *
once2_threadfunc(void *arg)
{
	int num;

	PTHREAD_REQUIRE(pthread_once(&once, once2_ofunc));

	num = *(int *)arg;
	printf("Thread %d sees x with value %d\n", num, x);
	ATF_REQUIRE_EQ(x, 2);

	return NULL;
}