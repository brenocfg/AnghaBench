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
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run ; 

__attribute__((used)) static void
cond_wait(clockid_t clck, const char *msg) {
	pthread_t child;

	if (debug)
		printf( "**** %s clock wait starting\n", msg);
	ATF_REQUIRE_EQ(pthread_create(&child, NULL, run, &clck), 0);
	ATF_REQUIRE_EQ(pthread_join(child, NULL), 0); /* wait for terminate */
	if (debug)
		printf( "**** %s clock wait ended\n", msg);
}