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
struct ib_device {int /*<<< orphan*/  client_data_lock; int /*<<< orphan*/  client_data_list; int /*<<< orphan*/  name; } ;
struct ib_client_data {int going_down; int /*<<< orphan*/  list; int /*<<< orphan*/ * data; struct ib_client* client; } ;
struct ib_client {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct ib_client_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lists_rwsem ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_client_context(struct ib_device *device, struct ib_client *client)
{
	struct ib_client_data *context;
	unsigned long flags;

	context = kmalloc(sizeof *context, GFP_KERNEL);
	if (!context) {
		pr_warn("Couldn't allocate client context for %s/%s\n",
			device->name, client->name);
		return -ENOMEM;
	}

	context->client = client;
	context->data   = NULL;
	context->going_down = false;

	down_write(&lists_rwsem);
	spin_lock_irqsave(&device->client_data_lock, flags);
	list_add(&context->list, &device->client_data_list);
	spin_unlock_irqrestore(&device->client_data_lock, flags);
	up_write(&lists_rwsem);

	return 0;
}