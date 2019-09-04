#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  client_t ;

/* Variables and functions */
 int /*<<< orphan*/  SV_CloseDownload (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SV_Netchan_FreeQueue (int /*<<< orphan*/ *) ; 

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