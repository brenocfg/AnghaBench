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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 uintptr_t BD_F_SB16 ; 
 uintptr_t BD_F_SB16X ; 
 uintptr_t BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 
 int ENXIO ; 
 uintptr_t SCF_PCM ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,char*) ; 

__attribute__((used)) static int
sb16_probe(device_t dev)
{
    	char buf[64];
	uintptr_t func, ver, r, f;

	/* The parent device has already been probed. */
	r = BUS_READ_IVAR(device_get_parent(dev), dev, 0, &func);
	if (func != SCF_PCM)
		return (ENXIO);

	r = BUS_READ_IVAR(device_get_parent(dev), dev, 1, &ver);
	f = (ver & 0xffff0000) >> 16;
	ver &= 0x0000ffff;
	if (f & BD_F_SB16) {
		snprintf(buf, sizeof buf, "SB16 DSP %d.%02d%s", (int) ver >> 8, (int) ver & 0xff,
			 (f & BD_F_SB16X)? " (ViBRA16X)" : "");
    		device_set_desc_copy(dev, buf);
		return 0;
	} else
		return (ENXIO);
}