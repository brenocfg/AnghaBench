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
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 int /*<<< orphan*/  canreturn ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  rump_sys_read (int,int*,int) ; 

__attribute__((used)) static void *
wrk(void *arg)
{
	int fd = (uintptr_t)arg;

	rump_sys_read(fd, &fd, sizeof(fd));
	if (!canreturn)
		errx(1, "should not have returned");
	if (fd != 37)
		errx(1, "got invalid magic");

	return NULL;
}