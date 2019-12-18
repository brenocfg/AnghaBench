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
 uintptr_t BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 
 int /*<<< orphan*/  EMU_VAR_FUNC ; 
 int /*<<< orphan*/  EMU_VAR_ROUTE ; 
 int ENXIO ; 
#define  RT_CENTER 133 
#define  RT_FRONT 132 
#define  RT_MCHRECORD 131 
#define  RT_REAR 130 
#define  RT_SIDE 129 
#define  RT_SUB 128 
 uintptr_t SCF_PCM ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int
emu_pcm_probe(device_t dev)
{
	uintptr_t func, route, r;
	const char *rt;
	char buffer[255];

	r = BUS_READ_IVAR(device_get_parent(dev), dev, EMU_VAR_FUNC, &func);

	if (func != SCF_PCM)
		return (ENXIO);

	rt = "UNKNOWN";
	r = BUS_READ_IVAR(device_get_parent(dev), dev, EMU_VAR_ROUTE, &route);
	switch (route) {
	case RT_FRONT:
		rt = "front";
		break;
	case RT_REAR:
		rt = "rear";
		break;
	case RT_CENTER:
		rt = "center";
		break;
	case RT_SUB:
		rt = "subwoofer";
		break;
	case RT_SIDE:
		rt = "side";
		break;
	case RT_MCHRECORD:
		rt = "multichannel recording";
		break;
	}

	snprintf(buffer, 255, "EMU10Kx DSP %s PCM interface", rt);
	device_set_desc_copy(dev, buffer);
	return (0);
}