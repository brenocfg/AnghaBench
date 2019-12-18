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
struct TYPE_5__ {int queuedVoipIndex; int queuedVoipPackets; int /*<<< orphan*/ * voipPacket; } ;
typedef  TYPE_1__ client_t ;

/* Variables and functions */
 int ARRAY_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SV_CloseDownload (TYPE_1__*) ; 
 int /*<<< orphan*/  SV_Netchan_FreeQueue (TYPE_1__*) ; 
 int /*<<< orphan*/  Z_Free (int /*<<< orphan*/ ) ; 

void SV_FreeClient(client_t *client)
{
#ifdef USE_VOIP
	int index;
	
	for(index = client->queuedVoipIndex; index < client->queuedVoipPackets; index++)
	{
		index %= ARRAY_LEN(client->voipPacket);
		
		Z_Free(client->voipPacket[index]);
	}
	
	client->queuedVoipPackets = 0;
#endif

	SV_Netchan_FreeQueue(client);
	SV_CloseDownload(client);
}