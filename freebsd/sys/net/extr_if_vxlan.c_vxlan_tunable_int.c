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
struct vxlan_softc {int vxl_unit; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char const*) ; 

__attribute__((used)) static int
vxlan_tunable_int(struct vxlan_softc *sc, const char *knob, int def)
{
	char path[64];

	snprintf(path, sizeof(path), "net.link.vxlan.%d.%s",
	    sc->vxl_unit, knob);
	TUNABLE_INT_FETCH(path, &def);

	return (def);
}