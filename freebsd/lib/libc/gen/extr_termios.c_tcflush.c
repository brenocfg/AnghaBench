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
 int /*<<< orphan*/  EINVAL ; 
 int FREAD ; 
 int FWRITE ; 
#define  TCIFLUSH 130 
#define  TCIOFLUSH 129 
#define  TCOFLUSH 128 
 int /*<<< orphan*/  TIOCFLUSH ; 
 int _ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  errno ; 

int
tcflush(int fd, int which)
{
	int com;

	switch (which) {
	case TCIFLUSH:
		com = FREAD;
		break;
	case TCOFLUSH:
		com = FWRITE;
		break;
	case TCIOFLUSH:
		com = FREAD | FWRITE;
		break;
	default:
		errno = EINVAL;
		return (-1);
	}
	return (_ioctl(fd, TIOCFLUSH, &com));
}