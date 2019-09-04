#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* next; int /*<<< orphan*/  msgBuffer; int /*<<< orphan*/  msg; } ;
typedef  TYPE_1__ netchan_buffer_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  cursize; } ;
typedef  TYPE_2__ msg_t ;
struct TYPE_12__ {scalar_t__ unsentFragments; } ;
struct TYPE_11__ {TYPE_6__ netchan; TYPE_1__** netchan_end_queue; scalar_t__ netchan_start_queue; } ;
typedef  TYPE_3__ client_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_DPrintf (char*) ; 
 int /*<<< orphan*/  MSG_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  MSG_WriteByte (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Netchan_Transmit (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_Malloc (int) ; 
 int /*<<< orphan*/  svc_EOF ; 

void SV_Netchan_Transmit( client_t *client, msg_t *msg)
{
	MSG_WriteByte( msg, svc_EOF );

	if(client->netchan.unsentFragments || client->netchan_start_queue)
	{
		netchan_buffer_t *netbuf;
		Com_DPrintf("#462 SV_Netchan_Transmit: unsent fragments, stacked\n");
		netbuf = (netchan_buffer_t *) Z_Malloc(sizeof(netchan_buffer_t));
		// store the msg, we can't store it encoded, as the encoding depends on stuff we still have to finish sending
		MSG_Copy(&netbuf->msg, netbuf->msgBuffer, sizeof( netbuf->msgBuffer ), msg);
#ifdef LEGACY_PROTOCOL
		if(client->compat)
		{
			Q_strncpyz(netbuf->clientCommandString, client->lastClientCommandString,
				   sizeof(netbuf->clientCommandString));
		}
#endif
		netbuf->next = NULL;
		// insert it in the queue, the message will be encoded and sent later
		*client->netchan_end_queue = netbuf;
		client->netchan_end_queue = &(*client->netchan_end_queue)->next;
	}
	else
	{
#ifdef LEGACY_PROTOCOL
		if(client->compat)
			SV_Netchan_Encode(client, msg, client->lastClientCommandString);
#endif
		Netchan_Transmit( &client->netchan, msg->cursize, msg->data );
	}
}