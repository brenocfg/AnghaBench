#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; struct TYPE_4__* next; scalar_t__ release; int /*<<< orphan*/  to; void* data; } ;
typedef  TYPE_1__ packetQueue_t ;
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_5__ {float value; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (void*,void const*,int) ; 
 void* S_Malloc (int) ; 
 scalar_t__ Sys_Milliseconds () ; 
 TYPE_3__* com_timescale ; 
 TYPE_1__* packetQueue ; 

__attribute__((used)) static void NET_QueuePacket( int length, const void *data, netadr_t to,
	int offset )
{
	packetQueue_t *new, *next = packetQueue;

	if(offset > 999)
		offset = 999;

	new = S_Malloc(sizeof(packetQueue_t));
	new->data = S_Malloc(length);
	Com_Memcpy(new->data, data, length);
	new->length = length;
	new->to = to;
	new->release = Sys_Milliseconds() + (int)((float)offset / com_timescale->value);	
	new->next = NULL;

	if(!packetQueue) {
		packetQueue = new;
		return;
	}
	while(next) {
		if(!next->next) {
			next->next = new;
			return;
		}
		next = next->next;
	}
}