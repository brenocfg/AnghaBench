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
struct tty {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sc; } ;
struct TYPE_3__ {int unit; } ;

/* Variables and functions */
 int MAXCONS ; 
 int SC_CONSOLECTL ; 
 int SC_VTY (struct tty*) ; 
 TYPE_2__* sc_console ; 
 int sc_max_unit () ; 

__attribute__((used)) static int
scdevtounit(struct tty *tp)
{
    int vty = SC_VTY(tp);

    if (vty == SC_CONSOLECTL)
	return ((sc_console != NULL) ? sc_console->sc->unit : -1);
    else if ((vty < 0) || (vty >= MAXCONS*sc_max_unit()))
	return -1;
    else
	return vty/MAXCONS;
}