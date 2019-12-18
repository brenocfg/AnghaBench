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
struct TYPE_3__ {scalar_t__ name; scalar_t__ toporder; scalar_t__ propfraction; scalar_t__ cycleno; scalar_t__ index; scalar_t__ printflag; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 int DFNDEBUG ; 
 int PROPDEBUG ; 
 int debug ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

void
printname(nltype *selfp)
{

    if ( selfp -> name != 0 ) {
	printf( "%s" , selfp -> name );
#	ifdef DEBUG
	    if ( debug & DFNDEBUG ) {
		printf( "{%d} " , selfp -> toporder );
	    }
	    if ( debug & PROPDEBUG ) {
		printf( "%5.2f%% " , selfp -> propfraction );
	    }
#	endif /* DEBUG */
    }
    if ( selfp -> cycleno != 0 ) {
	printf( " <cycle %d>" , selfp -> cycleno );
    }
    if ( selfp -> index != 0 ) {
	if ( selfp -> printflag ) {
	    printf( " [%d]" , selfp -> index );
	} else {
	    printf( " (%d)" , selfp -> index );
	}
    }
}