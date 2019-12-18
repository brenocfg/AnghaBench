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
struct TYPE_3__ {int /*<<< orphan*/  pshadowBits; int /*<<< orphan*/  dlightBits; int /*<<< orphan*/  indexes; int /*<<< orphan*/  numIndexes; int /*<<< orphan*/  verts; int /*<<< orphan*/  numVerts; } ;
typedef  TYPE_1__ srfBspSurface_t ;

/* Variables and functions */
 scalar_t__ RB_SurfaceVaoCached (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_SurfaceVertsAndIndexes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void RB_SurfaceFace( srfBspSurface_t *srf ) {
	if (RB_SurfaceVaoCached(srf->numVerts, srf->verts, srf->numIndexes,
		srf->indexes, srf->dlightBits, srf->pshadowBits))
	{
		return;
	}

	RB_SurfaceVertsAndIndexes(srf->numVerts, srf->verts, srf->numIndexes,
			srf->indexes, srf->dlightBits, srf->pshadowBits);
}