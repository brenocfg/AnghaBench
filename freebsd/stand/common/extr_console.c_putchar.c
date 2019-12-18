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
struct TYPE_2__ {int c_flags; int /*<<< orphan*/  (* c_out ) (int) ;} ;

/* Variables and functions */
 int C_ACTIVEOUT ; 
 int C_PRESENTOUT ; 
 TYPE_1__** consoles ; 
 int /*<<< orphan*/  stub1 (int) ; 

void
putchar(int c)
{
    int		cons;

    /* Expand newlines */
    if (c == '\n')
	putchar('\r');

    for (cons = 0; consoles[cons] != NULL; cons++)
	if ((consoles[cons]->c_flags & (C_PRESENTOUT | C_ACTIVEOUT)) ==
	    (C_PRESENTOUT | C_ACTIVEOUT))
	    consoles[cons]->c_out(c);
}