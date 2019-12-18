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
typedef  int /*<<< orphan*/  td_thread_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 scalar_t__ TD_ERR_OK ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ td_thr_getname (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
iterateThreads5(td_thread_t *thread, void *arg)
{
	int *counter = (int *)arg;
	/* Arbitrarily short string buffer */
	char name[3];

	ATF_REQUIRE(td_thr_getname(thread, name, sizeof(name)) == TD_ERR_OK);

	printf("Thread name: %s\n", name);

	/* strlen(3) does not count including a '\0' character */
	ATF_REQUIRE(strlen(name) < sizeof(name));

	++(*counter);

	return TD_ERR_OK;
}