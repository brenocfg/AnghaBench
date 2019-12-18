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
typedef  int /*<<< orphan*/  u_char ;
struct termios {int /*<<< orphan*/ * c_cc; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  TCIOFF 131 
#define  TCION 130 
#define  TCOOFF 129 
#define  TCOON 128 
 int /*<<< orphan*/  TIOCSTART ; 
 int /*<<< orphan*/  TIOCSTOP ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  _POSIX_VDISABLE ; 
 int _ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _write (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 
 int tcgetattr (int,struct termios*) ; 

int
tcflow(int fd, int action)
{
	struct termios term;
	u_char c;

	switch (action) {
	case TCOOFF:
		return (_ioctl(fd, TIOCSTOP, 0));
	case TCOON:
		return (_ioctl(fd, TIOCSTART, 0));
	case TCION:
	case TCIOFF:
		if (tcgetattr(fd, &term) == -1)
			return (-1);
		c = term.c_cc[action == TCIOFF ? VSTOP : VSTART];
		if (c != _POSIX_VDISABLE && _write(fd, &c, sizeof(c)) == -1)
			return (-1);
		return (0);
	default:
		errno = EINVAL;
		return (-1);
	}
	/* NOTREACHED */
}