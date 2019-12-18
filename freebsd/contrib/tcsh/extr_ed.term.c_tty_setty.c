#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  d_ltc; int /*<<< orphan*/  d_lb; int /*<<< orphan*/  d_pc; int /*<<< orphan*/  d_tc; int /*<<< orphan*/  d_t; } ;
typedef  TYPE_1__ ttydata_t ;
typedef  int /*<<< orphan*/  ioctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  RETRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  TCSETAW ; 
 int /*<<< orphan*/  TIOCLSET ; 
 int /*<<< orphan*/  TIOCSETC ; 
 int /*<<< orphan*/  TIOCSETN ; 
 int /*<<< orphan*/  TIOCSLTC ; 
 int /*<<< orphan*/  TIOCSPAGE ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xtcsetattr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
tty_setty(int fd, ttydata_t *td)
{
#ifdef POSIX
    RETRY(xtcsetattr(fd, TCSADRAIN, &td->d_t)); 
#else
# ifdef TERMIO
    RETRY(ioctl(fd, TCSETAW,    (ioctl_t) &td->d_t));
# else
#  ifdef TIOCSETN
    RETRY(ioctl(fd, TIOCSETN,  (ioctl_t) &td->d_t));
#  endif /* TIOCSETN */
#  ifdef TIOCGETC
    RETRY(ioctl(fd, TIOCSETC,  (ioctl_t) &td->d_tc));
#  endif /* TIOCGETC */
#  ifdef TIOCGPAGE
    RETRY(ioctl(fd, TIOCSPAGE, (ioctl_t) &td->d_pc));
#  endif /* TIOCGPAGE */
#  ifdef TIOCLGET
    RETRY(ioctl(fd, TIOCLSET,  (ioctl_t) &td->d_lb));
#  endif /* TIOCLGET */
# endif /* TERMIO */
#endif /* POSIX */

#ifdef TIOCGLTC
    RETRY(ioctl(fd, TIOCSLTC,  (ioctl_t) &td->d_ltc));
#endif /* TIOCGLTC */

    return 0;
}