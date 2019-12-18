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
union ioctl_arg {TYPE_1__ deallocate; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_address_handler ; 
 int release_client_resource (struct client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ioctl_deallocate(struct client *client, union ioctl_arg *arg)
{
	return release_client_resource(client, arg->deallocate.handle,
				       release_address_handler, NULL);
}