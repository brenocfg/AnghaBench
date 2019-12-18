#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {size_t header_length; int /*<<< orphan*/  header; int /*<<< orphan*/  cycle; int /*<<< orphan*/  closure; int /*<<< orphan*/  type; } ;
struct iso_interrupt_event {TYPE_1__ interrupt; int /*<<< orphan*/  event; } ;
struct fw_iso_context {int dummy; } ;
struct client {int /*<<< orphan*/  iso_closure; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_CDEV_EVENT_ISO_INTERRUPT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct iso_interrupt_event* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  queue_event (struct client*,int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iso_callback(struct fw_iso_context *context, u32 cycle,
			 size_t header_length, void *header, void *data)
{
	struct client *client = data;
	struct iso_interrupt_event *e;

	e = kmalloc(sizeof(*e) + header_length, GFP_ATOMIC);
	if (e == NULL)
		return;

	e->interrupt.type      = FW_CDEV_EVENT_ISO_INTERRUPT;
	e->interrupt.closure   = client->iso_closure;
	e->interrupt.cycle     = cycle;
	e->interrupt.header_length = header_length;
	memcpy(e->interrupt.header, header, header_length);
	queue_event(client, &e->event, &e->interrupt,
		    sizeof(e->interrupt) + header_length, NULL, 0);
}