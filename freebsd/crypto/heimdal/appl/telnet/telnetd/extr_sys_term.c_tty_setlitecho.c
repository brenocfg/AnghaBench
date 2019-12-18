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
struct TYPE_2__ {int /*<<< orphan*/  c_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHOCTL ; 
 int /*<<< orphan*/  TCTLECH ; 
 TYPE_1__ termbuf ; 

void
tty_setlitecho(int on)
{
# ifdef	ECHOCTL
    if (on)
	termbuf.c_lflag &= ~ECHOCTL;
    else
	termbuf.c_lflag |= ECHOCTL;
# endif
# ifdef	TCTLECH
    if (on)
	termbuf.c_lflag &= ~TCTLECH;
    else
	termbuf.c_lflag |= TCTLECH;
# endif
}