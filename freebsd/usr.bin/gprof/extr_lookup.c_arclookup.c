#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* name; TYPE_3__* children; } ;
typedef  TYPE_2__ nltype ;
struct TYPE_9__ {TYPE_2__* arc_childp; TYPE_1__* arc_parentp; struct TYPE_9__* arc_childlist; } ;
typedef  TYPE_3__ arctype ;
struct TYPE_7__ {char* name; } ;

/* Variables and functions */
 int LOOKUPDEBUG ; 
 int debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

arctype *
arclookup(nltype *parentp, nltype *childp)
{
    arctype	*arcp;

    if ( parentp == 0 || childp == 0 ) {
	fprintf( stderr, "[arclookup] parentp == 0 || childp == 0\n" );
	return 0;
    }
#   ifdef DEBUG
	if ( debug & LOOKUPDEBUG ) {
	    printf( "[arclookup] parent %s child %s\n" ,
		    parentp -> name , childp -> name );
	}
#   endif /* DEBUG */
    for ( arcp = parentp -> children ; arcp ; arcp = arcp -> arc_childlist ) {
#	ifdef DEBUG
	    if ( debug & LOOKUPDEBUG ) {
		printf( "[arclookup]\t arc_parent %s arc_child %s\n" ,
			arcp -> arc_parentp -> name ,
			arcp -> arc_childp -> name );
	    }
#	endif /* DEBUG */
	if ( arcp -> arc_childp == childp ) {
	    return arcp;
	}
    }
    return 0;
}