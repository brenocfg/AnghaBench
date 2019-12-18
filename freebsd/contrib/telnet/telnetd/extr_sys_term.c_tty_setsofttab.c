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
struct TYPE_3__ {int /*<<< orphan*/  sg_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  c_oflag; TYPE_1__ sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXTABS ; 
 int /*<<< orphan*/  TAB0 ; 
 int /*<<< orphan*/  TAB3 ; 
 int /*<<< orphan*/  TABDLY ; 
 int /*<<< orphan*/  XTABS ; 
 TYPE_2__ termbuf ; 

void
tty_setsofttab(int on)
{
#ifndef	USE_TERMIO
	if (on)
		termbuf.sg.sg_flags |= XTABS;
	else
		termbuf.sg.sg_flags &= ~XTABS;
#else
	if (on) {
# ifdef	OXTABS
		termbuf.c_oflag |= OXTABS;
# endif
# ifdef	TABDLY
		termbuf.c_oflag &= ~TABDLY;
		termbuf.c_oflag |= TAB3;
# endif
	} else {
# ifdef	OXTABS
		termbuf.c_oflag &= ~OXTABS;
# endif
# ifdef	TABDLY
		termbuf.c_oflag &= ~TABDLY;
		termbuf.c_oflag |= TAB0;
# endif
	}
#endif
}