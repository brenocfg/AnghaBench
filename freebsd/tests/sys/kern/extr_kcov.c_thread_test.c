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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,...) ; 
 int /*<<< orphan*/  KIODISABLE ; 
 int /*<<< orphan*/  KIOENABLE ; 
 int /*<<< orphan*/ * common_head (int*) ; 
 int /*<<< orphan*/  common_tail (int,int /*<<< orphan*/ *) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,size_t) ; 
 char** modes ; 
 size_t nitems (char**) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_test_helper ; 

__attribute__((used)) static void
thread_test(u_int mode)
{
	pthread_t thread;
	uint64_t *buf;
	int fd;

	buf = common_head(&fd);

	ATF_REQUIRE_MSG(ioctl(fd, KIOENABLE, mode) == 0,
	    "Unable to enable kcov %s",
	    mode < nitems(modes) ? modes[mode] : "unknown mode");

	pthread_create(&thread, NULL, thread_test_helper, buf);
	pthread_join(thread, NULL);

	ATF_REQUIRE_MSG(ioctl(fd, KIODISABLE, 0) == 0,
	    "Unable to disable kcov");

	common_tail(fd, buf);
}