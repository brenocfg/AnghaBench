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
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  resolvloop ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static void
run(int *nhosts)
{
	pthread_t self;
	int rc;

	self = pthread_self();
	rc = pthread_create(&self, NULL, resolvloop, nhosts);
	ATF_REQUIRE_MSG(rc == 0, "pthread_create failed: %s", strerror(rc));
}