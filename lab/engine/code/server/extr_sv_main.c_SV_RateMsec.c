#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; } ;
struct TYPE_9__ {int lastSentSize; int lastSentTime; TYPE_1__ remoteAddress; } ;
struct TYPE_10__ {int rate; TYPE_2__ netchan; } ;
typedef  TYPE_3__ client_t ;
struct TYPE_13__ {int value; } ;
struct TYPE_12__ {int integer; } ;
struct TYPE_11__ {int integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 scalar_t__ NA_IP6 ; 
 int Sys_Milliseconds () ; 
 scalar_t__ UDPIP6_HEADER_SIZE ; 
 scalar_t__ UDPIP_HEADER_SIZE ; 
 TYPE_6__* com_timescale ; 
 TYPE_5__* sv_maxRate ; 
 TYPE_4__* sv_minRate ; 

int SV_RateMsec(client_t *client)
{
	int rate, rateMsec;
	int messageSize;
	
	messageSize = client->netchan.lastSentSize;
	rate = client->rate;

	if(sv_maxRate->integer)
	{
		if(sv_maxRate->integer < 1000)
			Cvar_Set( "sv_MaxRate", "1000" );
		if(sv_maxRate->integer < rate)
			rate = sv_maxRate->integer;
	}

	if(sv_minRate->integer)
	{
		if(sv_minRate->integer < 1000)
			Cvar_Set("sv_minRate", "1000");
		if(sv_minRate->integer > rate)
			rate = sv_minRate->integer;
	}

	// check for unlimited rate
	if (rate == 0)
	{
		return 0;
	}

	if(client->netchan.remoteAddress.type == NA_IP6)
		messageSize += UDPIP6_HEADER_SIZE;
	else
		messageSize += UDPIP_HEADER_SIZE;
		
	rateMsec = messageSize * 1000 / ((int) (rate * com_timescale->value));
	rate = Sys_Milliseconds() - client->netchan.lastSentTime;
	
	if(rate > rateMsec)
		return 0;
	else
		return rateMsec - rate;
}