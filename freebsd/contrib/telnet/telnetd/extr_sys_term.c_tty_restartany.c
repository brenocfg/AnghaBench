#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int lflags; int c_iflag; } ;

/* Variables and functions */
 int DECCTQ ; 
 int IXANY ; 
 TYPE_1__ termbuf ; 

int
tty_restartany(void)
{
#ifndef USE_TERMIO
# ifdef	DECCTQ
	return((termbuf.lflags & DECCTQ) ? 0 : 1);
# else
	return(-1);
# endif
#else
	return((termbuf.c_iflag & IXANY) ? 1 : 0);
#endif
}