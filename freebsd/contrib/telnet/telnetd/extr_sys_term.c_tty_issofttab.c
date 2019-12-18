#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sg_flags; } ;
struct TYPE_4__ {int c_oflag; TYPE_1__ sg; } ;

/* Variables and functions */
 int OXTABS ; 
 int TAB3 ; 
 int TABDLY ; 
 int XTABS ; 
 TYPE_2__ termbuf ; 

int
tty_issofttab(void)
{
#ifndef	USE_TERMIO
	return (termbuf.sg.sg_flags & XTABS);
#else
# ifdef	OXTABS
	return (termbuf.c_oflag & OXTABS);
# endif
# ifdef	TABDLY
	return ((termbuf.c_oflag & TABDLY) == TAB3);
# endif
#endif
}