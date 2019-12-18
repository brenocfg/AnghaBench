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
struct promisor_remote {struct promisor_remote* next; } ;

/* Variables and functions */
 struct promisor_remote* promisors ; 
 struct promisor_remote** promisors_tail ; 

__attribute__((used)) static void promisor_remote_move_to_tail(struct promisor_remote *r,
					 struct promisor_remote *previous)
{
	if (r->next == NULL)
		return;

	if (previous)
		previous->next = r->next;
	else
		promisors = r->next ? r->next : r;
	r->next = NULL;
	*promisors_tail = r;
	promisors_tail = &r->next;
}