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
struct fw_cdev_flush_iso {scalar_t__ handle; } ;
union ioctl_arg {struct fw_cdev_flush_iso flush_iso; } ;
struct client {int /*<<< orphan*/ * iso_context; } ;

/* Variables and functions */
 int EINVAL ; 
 int fw_iso_context_flush_completions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioctl_flush_iso(struct client *client, union ioctl_arg *arg)
{
	struct fw_cdev_flush_iso *a = &arg->flush_iso;

	if (client->iso_context == NULL || a->handle != 0)
		return -EINVAL;

	return fw_iso_context_flush_completions(client->iso_context);
}