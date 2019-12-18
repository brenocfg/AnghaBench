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
struct server_request {struct server_reply_item* additional; struct server_reply_item* authority; struct server_reply_item* answer; } ;
struct server_reply_item {struct server_reply_item* data; struct server_reply_item* name; struct server_reply_item* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  mm_free (struct server_reply_item*) ; 

__attribute__((used)) static void
server_request_free_answers(struct server_request *req)
{
	struct server_reply_item *victim, *next, **list;
	int i;
	for (i = 0; i < 3; ++i) {
		if (i==0)
			list = &req->answer;
		else if (i==1)
			list = &req->authority;
		else
			list = &req->additional;

		victim = *list;
		while (victim) {
			next = victim->next;
			mm_free(victim->name);
			if (victim->data)
				mm_free(victim->data);
			mm_free(victim);
			victim = next;
		}
		*list = NULL;
	}
}