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
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
union ioctl_arg {TYPE_1__ remove_descriptor; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int release_client_resource (struct client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_descriptor ; 

__attribute__((used)) static int ioctl_remove_descriptor(struct client *client, union ioctl_arg *arg)
{
	return release_client_resource(client, arg->remove_descriptor.handle,
				       release_descriptor, NULL);
}