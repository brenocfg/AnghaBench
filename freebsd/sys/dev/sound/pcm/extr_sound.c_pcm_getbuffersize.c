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
struct snddev_info {int bufsz; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RANGE (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

unsigned int
pcm_getbuffersize(device_t dev, unsigned int minbufsz, unsigned int deflt, unsigned int maxbufsz)
{
	struct snddev_info *d = device_get_softc(dev);
	int sz, x;

	sz = 0;
	if (resource_int_value(device_get_name(dev), device_get_unit(dev), "buffersize", &sz) == 0) {
		x = sz;
		RANGE(sz, minbufsz, maxbufsz);
		if (x != sz)
			device_printf(dev, "'buffersize=%d' hint is out of range (%d-%d), using %d\n", x, minbufsz, maxbufsz, sz);
		x = minbufsz;
		while (x < sz)
			x <<= 1;
		if (x > sz)
			x >>= 1;
		if (x != sz) {
			device_printf(dev, "'buffersize=%d' hint is not a power of 2, using %d\n", sz, x);
			sz = x;
		}
	} else {
		sz = deflt;
	}

	d->bufsz = sz;

	return sz;
}