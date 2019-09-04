#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ evType; int evValue; int evValue2; int evTime; int evPtrLength; void* evPtr; } ;
typedef  TYPE_1__ sysEvent_t ;
typedef  scalar_t__ sysEventType_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int MASK_QUEUED_EVENTS ; 
 int MAX_QUEUED_EVENTS ; 
 scalar_t__ SE_MOUSE ; 
 int Sys_Milliseconds () ; 
 int /*<<< orphan*/  Z_Free (void*) ; 
 int eventHead ; 
 TYPE_1__* eventQueue ; 
 int eventTail ; 

void Com_QueueEvent( int time, sysEventType_t type, int value, int value2, int ptrLength, void *ptr )
{
	sysEvent_t  *ev;

	// combine mouse movement with previous mouse event
	if ( type == SE_MOUSE && eventHead != eventTail )
	{
		ev = &eventQueue[ ( eventHead + MAX_QUEUED_EVENTS - 1 ) & MASK_QUEUED_EVENTS ];

		if ( ev->evType == SE_MOUSE )
		{
			ev->evValue += value;
			ev->evValue2 += value2;
			return;
		}
	}

	ev = &eventQueue[ eventHead & MASK_QUEUED_EVENTS ];

	if ( eventHead - eventTail >= MAX_QUEUED_EVENTS )
	{
		Com_Printf("Com_QueueEvent: overflow\n");
		// we are discarding an event, but don't leak memory
		if ( ev->evPtr )
		{
			Z_Free( ev->evPtr );
		}
		eventTail++;
	}

	eventHead++;

	if ( time == 0 )
	{
		time = Sys_Milliseconds();
	}

	ev->evTime = time;
	ev->evType = type;
	ev->evValue = value;
	ev->evValue2 = value2;
	ev->evPtrLength = ptrLength;
	ev->evPtr = ptr;
}