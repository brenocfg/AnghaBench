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
struct TYPE_4__ {int toporder; struct TYPE_4__* cnext; struct TYPE_4__* cyclehead; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 int DFNDEBUG ; 
 int debug ; 
 int dfn_counter ; 
 int dfn_depth ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printname (TYPE_1__*) ; 

void
dfn_post_visit(nltype *parentp)
{
    nltype	*memberp;

#   ifdef DEBUG
	if ( debug & DFNDEBUG ) {
	    printf( "[dfn_post_visit]\t%d: " , dfn_depth );
	    printname( parentp );
	    printf( "\n" );
	}
#   endif /* DEBUG */
	/*
	 *	number functions and things in their cycles
	 *	unless the function is itself part of a cycle
	 */
    if ( parentp -> cyclehead == parentp ) {
	dfn_counter += 1;
	for ( memberp = parentp ; memberp ; memberp = memberp -> cnext ) {
	    memberp -> toporder = dfn_counter;
#	    ifdef DEBUG
		if ( debug & DFNDEBUG ) {
		    printf( "[dfn_post_visit]\t\tmember " );
		    printname( memberp );
		    printf( " -> toporder = %d\n" , dfn_counter );
		}
#	    endif /* DEBUG */
	}
    } else {
#	ifdef DEBUG
	    if ( debug & DFNDEBUG ) {
		printf( "[dfn_post_visit]\t\tis part of a cycle\n" );
	    }
#	endif /* DEBUG */
    }
    dfn_depth -= 1;
}