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
struct TYPE_3__ {int index; int propself; int propchild; int cycleno; int /*<<< orphan*/  selfcalls; int /*<<< orphan*/  npropcall; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 int BUFSIZ ; 
 double hz ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int printtime ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
printcycle(nltype *cyclep)
{
    char	kirkbuffer[ BUFSIZ ];

    sprintf( kirkbuffer , "[%d]" , cyclep -> index );
    printf( "%-6.6s %5.1f %7.2f %11.2f %7ld" ,
	    kirkbuffer ,
	    100 * ( cyclep -> propself + cyclep -> propchild ) / printtime ,
	    cyclep -> propself / hz ,
	    cyclep -> propchild / hz ,
	    cyclep -> npropcall );
    if ( cyclep -> selfcalls != 0 ) {
	printf( "+%-7ld" , cyclep -> selfcalls );
    } else {
	printf( " %7.7s" , "" );
    }
    printf( " <cycle %d as a whole>\t[%d]\n" ,
	    cyclep -> cycleno , cyclep -> index );
}