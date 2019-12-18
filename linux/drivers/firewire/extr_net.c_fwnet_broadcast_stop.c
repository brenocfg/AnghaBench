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
struct fwnet_device {scalar_t__ broadcast_state; int /*<<< orphan*/  broadcast_rcv_context; } ;

/* Variables and functions */
 scalar_t__ FWNET_BROADCAST_ERROR ; 
 int /*<<< orphan*/  __fwnet_broadcast_stop (struct fwnet_device*) ; 
 int /*<<< orphan*/  fw_iso_context_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fwnet_broadcast_stop(struct fwnet_device *dev)
{
	if (dev->broadcast_state == FWNET_BROADCAST_ERROR)
		return;
	fw_iso_context_stop(dev->broadcast_rcv_context);
	__fwnet_broadcast_stop(dev);
}