#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {int faceflags; int planenum; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_7__ {scalar_t__ phys_maxsteepness; int /*<<< orphan*/  phys_gravitydirection; } ;
struct TYPE_6__ {int /*<<< orphan*/  normal; } ;

/* Variables and functions */
 scalar_t__ DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FACE_GROUND ; 
 int FACE_SOLID ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorInverse (int /*<<< orphan*/ ) ; 
 TYPE_3__ cfg ; 
 TYPE_2__* mapplanes ; 

int AAS_GapFace(tmp_face_t *tmpface, int side)
{
	vec3_t invgravity;

	//if the face is a solid or ground face it can't be a gap
	if (tmpface->faceflags & (FACE_GROUND | FACE_SOLID)) return 0;

	VectorCopy(cfg.phys_gravitydirection, invgravity);
	VectorInverse(invgravity);

	return (DotProduct(invgravity, mapplanes[tmpface->planenum ^ side].normal) > cfg.phys_maxsteepness);
}