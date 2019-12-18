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
struct mdesc_notifier_client {struct mdesc_notifier_client* next; } ;
struct mdesc_handle {int dummy; } ;

/* Variables and functions */
 struct mdesc_notifier_client* client_list ; 
 int /*<<< orphan*/  notify_one (struct mdesc_notifier_client*,struct mdesc_handle*,struct mdesc_handle*) ; 

__attribute__((used)) static void mdesc_notify_clients(struct mdesc_handle *old_hp,
				 struct mdesc_handle *new_hp)
{
	struct mdesc_notifier_client *p = client_list;

	while (p) {
		notify_one(p, old_hp, new_hp);
		p = p->next;
	}
}