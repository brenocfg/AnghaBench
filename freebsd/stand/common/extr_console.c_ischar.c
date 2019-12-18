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
struct TYPE_2__ {int c_flags; scalar_t__ (* c_ready ) () ;} ;

/* Variables and functions */
 int C_ACTIVEIN ; 
 int C_PRESENTIN ; 
 TYPE_1__** consoles ; 
 scalar_t__ stub1 () ; 

int
ischar(void)
{
    int		cons;

    for (cons = 0; consoles[cons] != NULL; cons++)
	if ((consoles[cons]->c_flags & (C_PRESENTIN | C_ACTIVEIN)) ==
	    (C_PRESENTIN | C_ACTIVEIN) &&
	    (consoles[cons]->c_ready() != 0))
		return(1);
    return(0);
}