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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 scalar_t__ NS_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ func1 () ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  thrfunc ; 

int
main(int argc, char *argv[])
{
	pthread_t thr;
	void *threval;

	assert(pthread_create(&thr, NULL, thrfunc, NULL) == 0);
	assert(func1() == NS_SUCCESS);
	assert(pthread_join(thr, &threval) == 0);
}