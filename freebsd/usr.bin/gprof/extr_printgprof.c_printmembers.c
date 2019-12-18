#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double propself; double propchild; int /*<<< orphan*/  selfcalls; int /*<<< orphan*/  npropcall; struct TYPE_5__* cnext; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 double hz ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printname (TYPE_1__*) ; 
 int /*<<< orphan*/  sortmembers (TYPE_1__*) ; 

void
printmembers(nltype *cyclep)
{
    nltype	*memberp;

    sortmembers( cyclep );
    for ( memberp = cyclep -> cnext ; memberp ; memberp = memberp -> cnext ) {
	printf( "%6.6s %5.5s %7.2f %11.2f %7ld" ,
		"" , "" , memberp -> propself / hz , memberp -> propchild / hz ,
		memberp -> npropcall );
	if ( memberp -> selfcalls != 0 ) {
	    printf( "+%-7ld" , memberp -> selfcalls );
	} else {
	    printf( " %7.7s" , "" );
	}
	printf( "     " );
	printname( memberp );
	printf( "\n" );
    }
}