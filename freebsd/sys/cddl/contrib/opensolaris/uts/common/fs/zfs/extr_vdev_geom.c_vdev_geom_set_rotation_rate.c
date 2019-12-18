#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vdev_nonrot; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint16_t ;
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int g_getattr (char*,struct g_consumer*,int*) ; 

__attribute__((used)) static void
vdev_geom_set_rotation_rate(vdev_t *vd, struct g_consumer *cp)
{ 
	int error;
	uint16_t rate;

	error = g_getattr("GEOM::rotation_rate", cp, &rate);
	if (error == 0 && rate == 1)
		vd->vdev_nonrot = B_TRUE;
	else
		vd->vdev_nonrot = B_FALSE;
}