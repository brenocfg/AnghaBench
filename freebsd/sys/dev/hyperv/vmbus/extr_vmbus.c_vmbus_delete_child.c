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
struct vmbus_channel {int /*<<< orphan*/ * ch_dev; TYPE_1__* ch_vmbus; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmbus_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
vmbus_delete_child(struct vmbus_channel *chan)
{
	int error = 0;

	mtx_lock(&Giant);
	if (chan->ch_dev != NULL) {
		error = device_delete_child(chan->ch_vmbus->vmbus_dev,
		    chan->ch_dev);
		chan->ch_dev = NULL;
	}
	mtx_unlock(&Giant);
	return (error);
}