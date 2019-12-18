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
struct TYPE_2__ {int lflags; int c_lflag; } ;

/* Variables and functions */
 int ECHOCTL ; 
 int LCTLECH ; 
 int TCTLECH ; 
 TYPE_1__ termbuf ; 

int
tty_islitecho(void)
{
#ifndef	USE_TERMIO
	return (!(termbuf.lflags & LCTLECH));
#else
# ifdef	ECHOCTL
	return (!(termbuf.c_lflag & ECHOCTL));
# endif
# ifdef	TCTLECH
	return (!(termbuf.c_lflag & TCTLECH));
# endif
# if	!defined(ECHOCTL) && !defined(TCTLECH)
	return (0);	/* assumes ctl chars are echoed '^x' */
# endif
#endif
}