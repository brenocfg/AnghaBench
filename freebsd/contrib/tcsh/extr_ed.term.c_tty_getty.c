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
 int /*<<< orphan*/  TCGETA ; 
 int /*<<< orphan*/  TIOCGETC ; 
 int /*<<< orphan*/  TIOCGETP ; 
 int /*<<< orphan*/  TIOCGLTC ; 
 int /*<<< orphan*/  TIOCGPAGE ; 
 int /*<<< orphan*/  TIOCLGET ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetattr (int,int /*<<< orphan*/ *) ; 

int
tty_getty(int fd, ttydata_t *td)
{
#ifdef POSIX
    RETRY(tcgetattr(fd, &td->d_t));
#else /* TERMIO || GSTTY */
# ifdef TERMIO
    RETRY(ioctl(fd, TCGETA,    (ioctl_t) &td->d_t));
# else /* GSTTY */
#  ifdef TIOCGETP
    RETRY(ioctl(fd, TIOCGETP,  (ioctl_t) &td->d_t));
#  endif /* TIOCGETP */
#  ifdef TIOCGETC
    RETRY(ioctl(fd, TIOCGETC,  (ioctl_t) &td->d_tc));
#  endif /* TIOCGETC */
#  ifdef TIOCGPAGE
    RETRY(ioctl(fd, TIOCGPAGE, (ioctl_t) &td->d_pc));
#  endif /* TIOCGPAGE */
#  ifdef TIOCLGET
    RETRY(ioctl(fd, TIOCLGET,  (ioctl_t) &td->d_lb));
#  endif /* TIOCLGET */
# endif /* TERMIO */
#endif /* POSIX */

#ifdef TIOCGLTC
    RETRY(ioctl(fd, TIOCGLTC,  (ioctl_t) &td->d_ltc));
#endif /* TIOCGLTC */

    return 0;
}