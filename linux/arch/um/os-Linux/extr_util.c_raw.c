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
struct termios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CATCH_EINTR (int) ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  cfmakeraw (struct termios*) ; 
 int errno ; 
 int tcgetattr (int,struct termios*) ; 
 int tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

int raw(int fd)
{
	struct termios tt;
	int err;

	CATCH_EINTR(err = tcgetattr(fd, &tt));
	if (err < 0)
		return -errno;

	cfmakeraw(&tt);

	CATCH_EINTR(err = tcsetattr(fd, TCSADRAIN, &tt));
	if (err < 0)
		return -errno;

	/*
	 * XXX tcsetattr could have applied only some changes
	 * (and cfmakeraw() is a set of changes)
	 */
	return 0;
}