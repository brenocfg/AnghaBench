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
struct input_event {int type; int code; int value; } ;
struct evdev_client {size_t ec_buffer_head; size_t ec_buffer_tail; size_t ec_buffer_ready; size_t ec_buffer_size; struct input_event* ec_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
evdev_client_dumpqueue(struct evdev_client *client)
{
	struct input_event *event;
	size_t i, head, tail, ready, size;

	head = client->ec_buffer_head;
	tail = client->ec_buffer_tail;
	ready = client->ec_buffer_ready;
	size = client->ec_buffer_size;

	printf("evdev client: %p\n", client);
	printf("event queue: head=%zu ready=%zu tail=%zu size=%zu\n",
	    head, ready, tail, size);

	printf("queue contents:\n");

	for (i = 0; i < size; i++) {
		event = &client->ec_buffer[i];
		printf("%zu: ", i);

		if (i < head || i > tail)
			printf("unused\n");
		else
			printf("type=%d code=%d value=%d ", event->type,
			    event->code, event->value);

		if (i == head)
			printf("<- head\n");
		else if (i == tail)
			printf("<- tail\n");
		else if (i == ready)
			printf("<- ready\n");
		else
			printf("\n");
	}
}