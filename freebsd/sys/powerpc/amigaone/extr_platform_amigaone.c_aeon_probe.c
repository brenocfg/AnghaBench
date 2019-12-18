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
typedef  int /*<<< orphan*/  platform_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  model ;

/* Variables and functions */
 int BUS_PROBE_SPECIFIC ; 
 int ENXIO ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aeon_probe(platform_t plat)
{
	phandle_t rootnode;
	char model[32];

	rootnode = OF_finddevice("/");

	if (OF_getprop(rootnode, "model", model, sizeof(model)) > 0) {
		if (strncmp(model, "varisys,", strlen("varisys,")) == 0)
			return (BUS_PROBE_SPECIFIC);
	}

	return (ENXIO);
}