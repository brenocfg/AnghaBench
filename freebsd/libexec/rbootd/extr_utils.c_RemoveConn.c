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
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ RMPCONN ;

/* Variables and functions */
 int /*<<< orphan*/  FreeConn (TYPE_1__*) ; 
 TYPE_1__* RmpConns ; 

void
RemoveConn(RMPCONN *rconn)
{
	RMPCONN *thisrconn, *lastrconn;

	if (RmpConns == rconn) {		/* easy case */
		RmpConns = RmpConns->next;
		FreeConn(rconn);
	} else {				/* must traverse linked list */
		lastrconn = RmpConns;			/* set back ptr */
		thisrconn = lastrconn->next;		/* set current ptr */
		while (thisrconn != NULL) {
			if (rconn == thisrconn) {		/* found it */
				lastrconn->next = thisrconn->next;
				FreeConn(thisrconn);
				break;
			}
			lastrconn = thisrconn;
			thisrconn = thisrconn->next;
		}
	}
}