#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cursize; } ;
struct TYPE_7__ {struct TYPE_7__* next; TYPE_1__ msg; } ;
typedef  TYPE_2__ netchan_buffer_t ;
struct TYPE_8__ {TYPE_2__* netchan_start_queue; TYPE_2__** netchan_end_queue; int /*<<< orphan*/  netchan; } ;
typedef  TYPE_3__ client_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*) ; 
 int /*<<< orphan*/  Netchan_Transmit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_Free (TYPE_2__*) ; 

void SV_Netchan_TransmitNextInQueue(client_t *client)
{
	netchan_buffer_t *netbuf;
		
	Com_DPrintf("#462 Netchan_TransmitNextFragment: popping a queued message for transmit\n");
	netbuf = client->netchan_start_queue;

#ifdef LEGACY_PROTOCOL
	if(client->compat)
		SV_Netchan_Encode(client, &netbuf->msg, netbuf->clientCommandString);
#endif

	Netchan_Transmit(&client->netchan, netbuf->msg.cursize, netbuf->msg.data);

	// pop from queue
	client->netchan_start_queue = netbuf->next;
	if(!client->netchan_start_queue)
	{
		Com_DPrintf("#462 Netchan_TransmitNextFragment: emptied queue\n");
		client->netchan_end_queue = &client->netchan_start_queue;
	}
	else
		Com_DPrintf("#462 Netchan_TransmitNextFragment: remaining queued message\n");

	Z_Free(netbuf);
}