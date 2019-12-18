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
typedef  int /*<<< orphan*/ * vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AngleNormalize180 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InverseRotation (float const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (float const*,float const*,int /*<<< orphan*/ *) ; 
 float fabs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  vectoangles (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

qboolean InFov(const float start[3], const float end[3], const float angles[3], float fov) {
	vec3_t dir, view_angles;
	float hfov = fov * 0.5;
	VectorSubtract( end, start, dir );
	InverseRotation( angles, dir, qfalse );
	vectoangles( dir, view_angles );
	return fabs(AngleNormalize180(view_angles[0])) < hfov &&
				 fabs(AngleNormalize180(view_angles[1])) < hfov ? qtrue : qfalse;
}