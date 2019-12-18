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
typedef  scalar_t__ uint16_t ;
struct virtio_ident {char const* name; scalar_t__ devid; } ;

/* Variables and functions */
 struct virtio_ident* virtio_ident_table ; 

const char *
virtio_device_name(uint16_t devid)
{
	struct virtio_ident *ident;

	for (ident = virtio_ident_table; ident->name != NULL; ident++) {
		if (ident->devid == devid)
			return (ident->name);
	}

	return (NULL);
}