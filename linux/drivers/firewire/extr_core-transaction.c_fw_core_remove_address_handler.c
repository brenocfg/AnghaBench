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
struct fw_address_handler {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  address_handler_list_lock ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void fw_core_remove_address_handler(struct fw_address_handler *handler)
{
	spin_lock(&address_handler_list_lock);
	list_del_rcu(&handler->link);
	spin_unlock(&address_handler_list_lock);
	synchronize_rcu();
}