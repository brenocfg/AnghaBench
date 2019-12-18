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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;
struct wps_registrar_device {TYPE_1__ dev; struct wps_registrar_device* next; } ;
struct wps_registrar {struct wps_registrar_device* devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wps_registrar_device * wps_device_get(struct wps_registrar *reg,
						    const u8 *addr)
{
	struct wps_registrar_device *dev;

	for (dev = reg->devices; dev; dev = dev->next) {
		if (os_memcmp(dev->dev.mac_addr, addr, ETH_ALEN) == 0)
			return dev;
	}
	return NULL;
}