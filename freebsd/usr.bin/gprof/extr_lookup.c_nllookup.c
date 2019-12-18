#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long value; char* name; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 int LOOKUPDEBUG ; 
 int debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* nl ; 
 int nname ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

nltype *
nllookup(unsigned long address)
{
    register long	low;
    register long	middle;
    register long	high;
#   ifdef DEBUG
	register int	probes;

	probes = 0;
#   endif /* DEBUG */
    for ( low = 0 , high = nname - 1 ; low != high ; ) {
#	ifdef DEBUG
	    probes += 1;
#	endif /* DEBUG */
	middle = ( high + low ) >> 1;
	if ( nl[ middle ].value <= address && nl[ middle+1 ].value > address ) {
#	    ifdef DEBUG
		if ( debug & LOOKUPDEBUG ) {
		    printf( "[nllookup] %d (%d) probes\n" , probes , nname-1 );
		}
#	    endif /* DEBUG */
#if defined(__arm__)
	if (nl[middle].name[0] == '$' &&
	    nl[middle-1].value == nl[middle].value)
		middle--;
#endif

	    return &nl[ middle ];
	}
	if ( nl[ middle ].value > address ) {
	    high = middle;
	} else {
	    low = middle + 1;
	}
    }
#   ifdef DEBUG
	if ( debug & LOOKUPDEBUG ) {
	    fprintf( stderr , "[nllookup] (%d) binary search fails\n" ,
		nname-1 );
	}
#   endif /* DEBUG */
    return 0;
}