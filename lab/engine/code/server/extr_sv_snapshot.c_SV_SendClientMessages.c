#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ type; } ;
struct TYPE_10__ {TYPE_7__ remoteAddress; scalar_t__ unsentFragments; } ;
struct TYPE_11__ {int lastSnapshotTime; int snapshotMsec; void* rateDelayed; TYPE_1__ netchan; scalar_t__ netchan_start_queue; scalar_t__* downloadName; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ client_t ;
struct TYPE_15__ {int value; } ;
struct TYPE_14__ {scalar_t__ integer; } ;
struct TYPE_13__ {int integer; } ;
struct TYPE_12__ {int time; TYPE_2__* clients; } ;

/* Variables and functions */
 scalar_t__ NA_LOOPBACK ; 
 scalar_t__ SV_RateMsec (TYPE_2__*) ; 
 int /*<<< orphan*/  SV_SendClientSnapshot (TYPE_2__*) ; 
 scalar_t__ Sys_IsLANAddress (TYPE_7__) ; 
 TYPE_6__* com_timescale ; 
 void* qfalse ; 
 void* qtrue ; 
 TYPE_5__* sv_lanForceRate ; 
 TYPE_4__* sv_maxclients ; 
 TYPE_3__ svs ; 

void SV_SendClientMessages(void)
{
	int		i;
	client_t	*c;

	// send a message to each connected client
	for(i=0; i < sv_maxclients->integer; i++)
	{
		c = &svs.clients[i];
		
		if(!c->state)
			continue;		// not connected

		if(*c->downloadName)
			continue;		// Client is downloading, don't send snapshots

		if(c->netchan.unsentFragments || c->netchan_start_queue)
		{
			c->rateDelayed = qtrue;
			continue;		// Drop this snapshot if the packet queue is still full or delta compression will break
		}

		if(!(c->netchan.remoteAddress.type == NA_LOOPBACK ||
		     (sv_lanForceRate->integer && Sys_IsLANAddress(c->netchan.remoteAddress))))
		{
			// rate control for clients not on LAN 
			
			if(svs.time - c->lastSnapshotTime < c->snapshotMsec * com_timescale->value)
				continue;		// It's not time yet

			if(SV_RateMsec(c) > 0)
			{
				// Not enough time since last packet passed through the line
				c->rateDelayed = qtrue;
				continue;
			}
		}

		// generate and send a new message
		SV_SendClientSnapshot(c);
		c->lastSnapshotTime = svs.time;
		c->rateDelayed = qfalse;
	}
}