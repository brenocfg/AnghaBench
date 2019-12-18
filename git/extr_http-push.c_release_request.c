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
struct transfer_request {struct transfer_request* url; struct transfer_request* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct transfer_request*) ; 
 struct transfer_request* request_queue_head ; 

__attribute__((used)) static void release_request(struct transfer_request *request)
{
	struct transfer_request *entry = request_queue_head;

	if (request == request_queue_head) {
		request_queue_head = request->next;
	} else {
		while (entry && entry->next != request)
			entry = entry->next;
		if (entry)
			entry->next = request->next;
	}

	free(request->url);
	free(request);
}