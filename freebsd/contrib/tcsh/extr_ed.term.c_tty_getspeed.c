#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int c_cflag; int sg_ispeed; } ;
struct TYPE_5__ {TYPE_3__ d_t; } ;
typedef  TYPE_1__ ttydata_t ;
typedef  int speed_t ;

/* Variables and functions */
 int CBAUD ; 
 int cfgetispeed (TYPE_3__*) ; 
 int cfgetospeed (TYPE_3__*) ; 

speed_t
tty_getspeed(ttydata_t *td)
{
    speed_t spd;

#ifdef POSIX
    if ((spd = cfgetispeed(&td->d_t)) == 0)
	spd = cfgetospeed(&td->d_t);
#else /* ! POSIX */
# ifdef TERMIO
#  ifdef CBAUD
    spd = td->d_t.c_cflag & CBAUD;
#  else 
    spd = 0;
#  endif 
# else /* SGTTY */
    spd = td->d_t.sg_ispeed;
# endif /* TERMIO */
#endif /* POSIX */

    return spd;
}