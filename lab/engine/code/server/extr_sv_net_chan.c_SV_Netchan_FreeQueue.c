#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ netchan_buffer_t ;
struct TYPE_6__ {TYPE_1__* netchan_start_queue; TYPE_1__** netchan_end_queue; } ;
typedef  TYPE_2__ client_t ;

/* Variables and functions */
 int /*<<< orphan*/  Z_Free (TYPE_1__*) ; 

void SV_Netchan_FreeQueue(client_t *client)
{
	netchan_buffer_t *netbuf, *next;
	
	for(netbuf = client->netchan_start_queue; netbuf; netbuf = next)
	{
		next = netbuf->next;
		Z_Free(netbuf);
	}
	
	client->netchan_start_queue = NULL;
	client->netchan_end_queue = &client->netchan_start_queue;
}