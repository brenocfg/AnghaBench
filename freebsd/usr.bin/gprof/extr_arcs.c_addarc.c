#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* parents; TYPE_2__* children; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ nltype ;
struct TYPE_9__ {long arc_count; struct TYPE_9__* arc_parentlist; struct TYPE_9__* arc_childlist; TYPE_1__* arc_childp; TYPE_1__* arc_parentp; } ;
typedef  TYPE_2__ arctype ;

/* Variables and functions */
 int TALLYDEBUG ; 
 TYPE_2__* arclookup (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ calloc (int,int) ; 
 int debug ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  printf (char*,long,long,...) ; 

void
addarc(nltype *parentp, nltype *childp, long count)
{
    arctype		*arcp;

#   ifdef DEBUG
	if ( debug & TALLYDEBUG ) {
	    printf( "[addarc] %ld arcs from %s to %s\n" ,
		    count , parentp -> name , childp -> name );
	}
#   endif /* DEBUG */
    arcp = arclookup( parentp , childp );
    if ( arcp != 0 ) {
	    /*
	     *	a hit:  just increment the count.
	     */
#	ifdef DEBUG
	    if ( debug & TALLYDEBUG ) {
		printf( "[tally] hit %ld += %ld\n" ,
			arcp -> arc_count , count );
	    }
#	endif /* DEBUG */
	arcp -> arc_count += count;
	return;
    }
    arcp = (arctype *)calloc( 1 , sizeof *arcp );
    if (arcp == NULL)
	errx( 1 , "malloc failed" );
    arcp -> arc_parentp = parentp;
    arcp -> arc_childp = childp;
    arcp -> arc_count = count;
	/*
	 *	prepend this child to the children of this parent
	 */
    arcp -> arc_childlist = parentp -> children;
    parentp -> children = arcp;
	/*
	 *	prepend this parent to the parents of this child
	 */
    arcp -> arc_parentlist = childp -> parents;
    childp -> parents = arcp;
}