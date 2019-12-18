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
struct TYPE_2__ {int /*<<< orphan*/ * pages; } ;
struct fwnet_device {scalar_t__ broadcast_state; int /*<<< orphan*/ * broadcast_rcv_buffer_ptrs; int /*<<< orphan*/ * broadcast_rcv_context; int /*<<< orphan*/  card; TYPE_1__ broadcast_rcv_buffer; } ;

/* Variables and functions */
 scalar_t__ FWNET_BROADCAST_ERROR ; 
 unsigned int FWNET_ISO_PAGE_COUNT ; 
 int /*<<< orphan*/  fw_iso_buffer_destroy (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __fwnet_broadcast_stop(struct fwnet_device *dev)
{
	unsigned u;

	if (dev->broadcast_state != FWNET_BROADCAST_ERROR) {
		for (u = 0; u < FWNET_ISO_PAGE_COUNT; u++)
			kunmap(dev->broadcast_rcv_buffer.pages[u]);
		fw_iso_buffer_destroy(&dev->broadcast_rcv_buffer, dev->card);
	}
	if (dev->broadcast_rcv_context) {
		fw_iso_context_destroy(dev->broadcast_rcv_context);
		dev->broadcast_rcv_context = NULL;
	}
	kfree(dev->broadcast_rcv_buffer_ptrs);
	dev->broadcast_rcv_buffer_ptrs = NULL;
	dev->broadcast_state = FWNET_BROADCAST_ERROR;
}