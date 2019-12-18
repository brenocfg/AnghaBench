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
union ioctl_arg {int /*<<< orphan*/  allocate_iso_resource; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISO_RES_DEALLOC_ONCE ; 
 int init_iso_resource (struct client*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ioctl_deallocate_iso_resource_once(struct client *client,
					      union ioctl_arg *arg)
{
	return init_iso_resource(client,
			&arg->allocate_iso_resource, ISO_RES_DEALLOC_ONCE);
}