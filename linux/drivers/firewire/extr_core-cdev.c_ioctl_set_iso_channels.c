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
struct fw_cdev_set_iso_channels {scalar_t__ handle; int /*<<< orphan*/  channels; } ;
union ioctl_arg {struct fw_cdev_set_iso_channels set_iso_channels; } ;
struct fw_iso_context {int dummy; } ;
struct client {struct fw_iso_context* iso_context; } ;

/* Variables and functions */
 int EINVAL ; 
 int fw_iso_context_set_channels (struct fw_iso_context*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioctl_set_iso_channels(struct client *client, union ioctl_arg *arg)
{
	struct fw_cdev_set_iso_channels *a = &arg->set_iso_channels;
	struct fw_iso_context *ctx = client->iso_context;

	if (ctx == NULL || a->handle != 0)
		return -EINVAL;

	return fw_iso_context_set_channels(ctx, &a->channels);
}