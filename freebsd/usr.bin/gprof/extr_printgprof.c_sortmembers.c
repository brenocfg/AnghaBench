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
struct TYPE_5__ {struct TYPE_5__* cnext; } ;
typedef  TYPE_1__ nltype ;

/* Variables and functions */
 scalar_t__ GREATERTHAN ; 
 scalar_t__ membercmp (TYPE_1__*,TYPE_1__*) ; 

void
sortmembers(nltype *cyclep)
{
    nltype	*todo;
    nltype	*doing;
    nltype	*prev;

	/*
	 *	detach cycle members from cyclehead,
	 *	and insertion sort them back on.
	 */
    todo = cyclep -> cnext;
    cyclep -> cnext = 0;
    for (  (doing = todo)&&(todo = doing -> cnext);
	    doing ;
	   (doing = todo )&&(todo = doing -> cnext )){
	for ( prev = cyclep ; prev -> cnext ; prev = prev -> cnext ) {
	    if ( membercmp( doing , prev -> cnext ) == GREATERTHAN ) {
		break;
	    }
	}
	doing -> cnext = prev -> cnext;
	prev -> cnext = doing;
    }
}