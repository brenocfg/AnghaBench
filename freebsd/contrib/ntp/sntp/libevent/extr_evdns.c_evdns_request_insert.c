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
struct request {struct request* prev; struct request* next; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_VALID_REQUEST (struct request*) ; 

__attribute__((used)) static void
evdns_request_insert(struct request *req, struct request **head) {
	ASSERT_LOCKED(req->base);
	ASSERT_VALID_REQUEST(req);
	if (!*head) {
		*head = req;
		req->next = req->prev = req;
		return;
	}

	req->prev = (*head)->prev;
	req->prev->next = req;
	req->next = *head;
	(*head)->prev = req;
}