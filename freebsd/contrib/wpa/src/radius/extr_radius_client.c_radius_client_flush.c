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
struct radius_msg_list {scalar_t__ msg_type; struct radius_msg_list* next; } ;
struct radius_client_data {struct radius_msg_list* msgs; int /*<<< orphan*/  num_msgs; } ;

/* Variables and functions */
 scalar_t__ RADIUS_AUTH ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct radius_client_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radius_client_msg_free (struct radius_msg_list*) ; 
 int /*<<< orphan*/  radius_client_timer ; 

void radius_client_flush(struct radius_client_data *radius, int only_auth)
{
	struct radius_msg_list *entry, *prev, *tmp;

	if (!radius)
		return;

	prev = NULL;
	entry = radius->msgs;

	while (entry) {
		if (!only_auth || entry->msg_type == RADIUS_AUTH) {
			if (prev)
				prev->next = entry->next;
			else
				radius->msgs = entry->next;

			tmp = entry;
			entry = entry->next;
			radius_client_msg_free(tmp);
			radius->num_msgs--;
		} else {
			prev = entry;
			entry = entry->next;
		}
	}

	if (radius->msgs == NULL)
		eloop_cancel_timeout(radius_client_timer, radius, NULL);
}