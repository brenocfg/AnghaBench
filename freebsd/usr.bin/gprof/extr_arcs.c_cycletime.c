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
struct TYPE_3__ {double propfraction; int time; int propself; struct TYPE_3__* cnext; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 TYPE_1__* cyclenl ; 
 int ncycle ; 

void
cycletime(void)
{
    int			cycle;
    nltype		*cyclenlp;
    nltype		*childp;

    for ( cycle = 1 ; cycle <= ncycle ; cycle += 1 ) {
	cyclenlp = &cyclenl[ cycle ];
	for ( childp = cyclenlp -> cnext ; childp ; childp = childp -> cnext ) {
	    if ( childp -> propfraction == 0.0 ) {
		    /*
		     * all members have the same propfraction except those
		     *	that were excluded with -E
		     */
		continue;
	    }
	    cyclenlp -> time += childp -> time;
	}
	cyclenlp -> propself = cyclenlp -> propfraction * cyclenlp -> time;
    }
}