#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ bot_consolemessage_t ;

/* Variables and functions */
 TYPE_1__* freeconsolemessages ; 

void FreeConsoleMessage(bot_consolemessage_t *message)
{
	if (freeconsolemessages) freeconsolemessages->prev = message;
	message->prev = NULL;
	message->next = freeconsolemessages;
	freeconsolemessages = message;
}