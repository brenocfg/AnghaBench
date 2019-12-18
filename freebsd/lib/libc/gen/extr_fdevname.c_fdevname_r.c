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
struct fiodgname_arg {char* buf; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIODGNAME ; 
 int _ioctl (int,int /*<<< orphan*/ ,struct fiodgname_arg*) ; 

char *
fdevname_r(int fd, char *buf, int len)
{
	struct fiodgname_arg fgn;

	fgn.buf = buf;
	fgn.len = len;

	if (_ioctl(fd, FIODGNAME, &fgn) == -1)
		return (NULL);
	return (buf);
}