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
 int BUS_PROBE_NOWILDCARD ; 
 int SC_AUTODETECT_KBD ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int sc_probe_unit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ofwfb_scprobe(device_t dev)
{
	int error;

	device_set_desc(dev, "System console");

	error = sc_probe_unit(device_get_unit(dev),
	    device_get_flags(dev) | SC_AUTODETECT_KBD);
	if (error != 0)
		return (error);

	/* This is a fake device, so make sure we added it ourselves */
	return (BUS_PROBE_NOWILDCARD);
}