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
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_DEBUG_POLYGON_CREATE ; 
 int syscall (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

int trap_DebugPolygonCreate(int color, int numPoints, vec3_t *points) {
	return syscall( G_DEBUG_POLYGON_CREATE, color, numPoints, points );
}