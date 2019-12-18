#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ncall; scalar_t__ selfcalls; scalar_t__ propself; scalar_t__ propchild; scalar_t__ name; scalar_t__ cycleno; int /*<<< orphan*/  printflag; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  gprofheader () ; 
 int /*<<< orphan*/  gprofline (TYPE_1__*) ; 
 int ncycle ; 
 int nname ; 
 int /*<<< orphan*/  printchildren (TYPE_1__*) ; 
 int /*<<< orphan*/  printcycle (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  printmembers (TYPE_1__*) ; 
 int /*<<< orphan*/  printparents (TYPE_1__*) ; 
 scalar_t__ zflag ; 

void
printgprof(nltype **timesortnlp)
{
    int		idx;
    nltype	*parentp;

	/*
	 *	Print out the structured profiling list
	 */
    gprofheader();
    for ( idx = 0 ; idx < nname + ncycle ; idx ++ ) {
	parentp = timesortnlp[ idx ];
	if ( zflag == 0 &&
	     parentp -> ncall == 0 &&
	     parentp -> selfcalls == 0 &&
	     parentp -> propself == 0 &&
	     parentp -> propchild == 0 ) {
	    continue;
	}
	if ( ! parentp -> printflag ) {
	    continue;
	}
	if ( parentp -> name == 0 && parentp -> cycleno != 0 ) {
		/*
		 *	cycle header
		 */
	    printcycle( parentp );
	    printmembers( parentp );
	} else {
	    printparents( parentp );
	    gprofline( parentp );
	    printchildren( parentp );
	}
	printf( "\n" );
	printf( "-----------------------------------------------\n" );
	printf( "\n" );
    }
    free( timesortnlp );
}