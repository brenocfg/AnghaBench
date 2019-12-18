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
typedef  int /*<<< orphan*/  daddr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int EROFS ; 
 int F_MASK ; 
 int F_READ ; 
 int F_WRITE ; 
 TYPE_1__ umass_uaa ; 
 scalar_t__ usb_msc_read_10 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*) ; 
 scalar_t__ usb_msc_write_10 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*) ; 

__attribute__((used)) static int
umass_disk_strategy(void *devdata, int flag, daddr_t dblk, size_t size,
    char *buf, size_t *rsizep)
{
	if (umass_uaa.device == NULL)
		return (ENXIO);
	if (rsizep != NULL)
		*rsizep = 0;

	flag &= F_MASK;
	if (flag == F_WRITE) {
		if (usb_msc_write_10(umass_uaa.device, 0, dblk, size >> 9, buf) != 0)
			return (EINVAL);
	} else if (flag == F_READ) {
		if (usb_msc_read_10(umass_uaa.device, 0, dblk, size >> 9, buf) != 0)
			return (EINVAL);
	} else {
		return (EROFS);
	}

	if (rsizep != NULL)
		*rsizep = size;
	return (0);
}