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
struct TYPE_4__ {int index; int propself; int propchild; int ncall; scalar_t__ selfcalls; int /*<<< orphan*/  npropcall; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 int BUFSIZ ; 
 double hz ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printname (TYPE_1__*) ; 
 int printtime ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
gprofline(register nltype *np)
{
    char	kirkbuffer[ BUFSIZ ];

    sprintf( kirkbuffer , "[%d]" , np -> index );
    printf( "%-6.6s %5.1f %7.2f %11.2f" ,
	    kirkbuffer ,
	    100 * ( np -> propself + np -> propchild ) / printtime ,
	    np -> propself / hz ,
	    np -> propchild / hz );
    if ( ( np -> ncall + np -> selfcalls ) != 0 ) {
	printf( " %7ld" , np -> npropcall );
	if ( np -> selfcalls != 0 ) {
	    printf( "+%-7ld " , np -> selfcalls );
	} else {
	    printf( " %7.7s " , "" );
	}
    } else {
	printf( " %7.7s %7.7s " , "" , "" );
    }
    printname( np );
    printf( "\n" );
}