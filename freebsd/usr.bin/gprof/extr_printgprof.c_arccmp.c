#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ cycleno; int /*<<< orphan*/  ncall; } ;
typedef  TYPE_1__ nltype ;
struct TYPE_7__ {double arc_time; double arc_childtime; scalar_t__ arc_count; TYPE_1__* arc_childp; TYPE_1__* arc_parentp; } ;
typedef  TYPE_2__ arctype ;

/* Variables and functions */
 int EQUALTO ; 
 int GREATERTHAN ; 
 int LESSTHAN ; 
 int TIMEDEBUG ; 
 int debug ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printname (TYPE_1__*) ; 

int
arccmp(arctype *thisp, arctype *thatp)
{
    nltype	*thisparentp = thisp -> arc_parentp;
    nltype	*thischildp = thisp -> arc_childp;
    nltype	*thatparentp = thatp -> arc_parentp;
    nltype	*thatchildp = thatp -> arc_childp;
    double	thistime;
    double	thattime;

#   ifdef DEBUG
	if ( debug & TIMEDEBUG ) {
	    printf( "[arccmp] " );
	    printname( thisparentp );
	    printf( " calls " );
	    printname ( thischildp );
	    printf( " %f + %f %ld/%ld\n" ,
		    thisp -> arc_time , thisp -> arc_childtime ,
		    thisp -> arc_count , thischildp -> ncall );
	    printf( "[arccmp] " );
	    printname( thatparentp );
	    printf( " calls " );
	    printname( thatchildp );
	    printf( " %f + %f %ld/%ld\n" ,
		    thatp -> arc_time , thatp -> arc_childtime ,
		    thatp -> arc_count , thatchildp -> ncall );
	    printf( "\n" );
	}
#   endif /* DEBUG */
    if ( thisparentp == thischildp ) {
	    /* this is a self call */
	return LESSTHAN;
    }
    if ( thatparentp == thatchildp ) {
	    /* that is a self call */
	return GREATERTHAN;
    }
    if ( thisparentp -> cycleno != 0 && thischildp -> cycleno != 0 &&
	thisparentp -> cycleno == thischildp -> cycleno ) {
	    /* this is a call within a cycle */
	if ( thatparentp -> cycleno != 0 && thatchildp -> cycleno != 0 &&
	    thatparentp -> cycleno == thatchildp -> cycleno ) {
		/* that is a call within the cycle, too */
	    if ( thisp -> arc_count < thatp -> arc_count ) {
		return LESSTHAN;
	    }
	    if ( thisp -> arc_count > thatp -> arc_count ) {
		return GREATERTHAN;
	    }
	    return EQUALTO;
	} else {
		/* that isn't a call within the cycle */
	    return LESSTHAN;
	}
    } else {
	    /* this isn't a call within a cycle */
	if ( thatparentp -> cycleno != 0 && thatchildp -> cycleno != 0 &&
	    thatparentp -> cycleno == thatchildp -> cycleno ) {
		/* that is a call within a cycle */
	    return GREATERTHAN;
	} else {
		/* neither is a call within a cycle */
	    thistime = thisp -> arc_time + thisp -> arc_childtime;
	    thattime = thatp -> arc_time + thatp -> arc_childtime;
	    if ( thistime < thattime )
		return LESSTHAN;
	    if ( thistime > thattime )
		return GREATERTHAN;
	    if ( thisp -> arc_count < thatp -> arc_count )
		return LESSTHAN;
	    if ( thisp -> arc_count > thatp -> arc_count )
		return GREATERTHAN;
	    return EQUALTO;
	}
    }
}