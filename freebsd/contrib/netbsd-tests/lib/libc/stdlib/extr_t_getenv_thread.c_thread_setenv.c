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
typedef  int /*<<< orphan*/  value ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK (int) ; 
 size_t THREADED_NUM_VARS ; 
 char* THREADED_VAR_NAME ; 
 size_t lrand48 () ; 
 int setenv (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,size_t) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
thread_setenv(void *arg)
{
	time_t endtime;

	endtime = *(time_t *)arg;
	do {
		size_t i;
		char name[32], value[64];

		i = lrand48() % THREADED_NUM_VARS;
		(void)snprintf(name, sizeof(name), THREADED_VAR_NAME, i);
		(void)snprintf(value, sizeof(value), "setenv %ld", lrand48());

		ATF_CHECK(setenv(name, value, 1) != -1);
	} while (time(NULL) < endtime);

	return NULL;
}