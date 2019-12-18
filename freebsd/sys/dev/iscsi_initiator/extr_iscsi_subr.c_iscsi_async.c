#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int asyncEvent; int /*<<< orphan*/  asyncVCode; } ;
struct TYPE_6__ {TYPE_4__ async; } ;
struct TYPE_8__ {TYPE_1__ ipdu; } ;
struct TYPE_7__ {TYPE_3__ pdu; } ;
typedef  TYPE_2__ pduq_t ;
typedef  TYPE_3__ pdu_t ;
typedef  int /*<<< orphan*/  isc_session_t ;
typedef  TYPE_4__ async_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  isc_stop_receiver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdebug (int,char*,int,int /*<<< orphan*/ ) ; 

void
iscsi_async(isc_session_t *sp, pduq_t *pq)
{
     pdu_t		*pp = &pq->pdu;
     async_t		*cmd = &pp->ipdu.async;

     debug_called(8);

     sdebug(3, "asyncevent=0x%x asyncVCode=0x%0x", cmd->asyncEvent, cmd->asyncVCode);
     switch(cmd->asyncEvent) {
     case 0: // check status ...
	  break;

     case 1: // target request logout
	  isc_stop_receiver(sp);	// XXX: temporary solution
	  break;

     case 2: // target indicates it wants to drop connection
	  isc_stop_receiver(sp);	// XXX: temporary solution
	  break;

     case 3: // target indicates it will drop all connections.
	  isc_stop_receiver(sp);	// XXX: temporary solution
	  break;

     case 4: // target request parameter negotiation
	  break;

     default:
	  break;
     }
}