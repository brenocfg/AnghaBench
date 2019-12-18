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
struct atheros_driver_data {int /*<<< orphan*/  iface; int /*<<< orphan*/  ioctl_sock; } ;

/* Variables and functions */
 int linux_set_iface_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
atheros_commit(void *priv)
{
	struct atheros_driver_data *drv = priv;
	return linux_set_iface_flags(drv->ioctl_sock, drv->iface, 1);
}