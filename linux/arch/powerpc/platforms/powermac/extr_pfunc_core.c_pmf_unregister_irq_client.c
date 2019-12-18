#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmf_irq_client {int /*<<< orphan*/  link; struct pmf_function* func; } ;
struct pmf_function {TYPE_2__* dev; int /*<<< orphan*/  irq_clients; } ;
struct TYPE_4__ {TYPE_1__* handlers; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* irq_disable ) (struct pmf_function*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmf_irq_mutex ; 
 int /*<<< orphan*/  pmf_lock ; 
 int /*<<< orphan*/  pmf_put_function (struct pmf_function*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pmf_function*) ; 

void pmf_unregister_irq_client(struct pmf_irq_client *client)
{
	struct pmf_function *func = client->func;
	unsigned long flags;

	BUG_ON(func == NULL);

	/* guard against manipulations of list */
	mutex_lock(&pmf_irq_mutex);
	client->func = NULL;

	/* guard against pmf_do_irq while changing list */
	spin_lock_irqsave(&pmf_lock, flags);
	list_del(&client->link);
	spin_unlock_irqrestore(&pmf_lock, flags);

	if (list_empty(&func->irq_clients))
		func->dev->handlers->irq_disable(func);
	mutex_unlock(&pmf_irq_mutex);
	pmf_put_function(func);
}