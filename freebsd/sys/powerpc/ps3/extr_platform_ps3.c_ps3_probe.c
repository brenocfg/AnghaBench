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
typedef  int /*<<< orphan*/  compatible ;

/* Variables and functions */
 int BUS_PROBE_NOWILDCARD ; 
 int BUS_PROBE_SPECIFIC ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
ps3_probe(platform_t plat)
{
	phandle_t root;
	char compatible[64];

	root = OF_finddevice("/");
	if (OF_getprop(root, "compatible", compatible, sizeof(compatible)) <= 0)
                return (BUS_PROBE_NOWILDCARD);
	
	if (strncmp(compatible, "sony,ps3", sizeof(compatible)) != 0)
		return (BUS_PROBE_NOWILDCARD);

	return (BUS_PROBE_SPECIFIC);
}