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
struct pmi_handler {int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  handler_spinlock; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* data ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int pmi_register_handler(struct pmi_handler *handler)
{
	if (!data)
		return -ENODEV;

	spin_lock(&data->handler_spinlock);
	list_add_tail(&handler->node, &data->handler);
	spin_unlock(&data->handler_spinlock);

	return 0;
}