#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  verts; int /*<<< orphan*/  indexes; int /*<<< orphan*/  heightLodError; int /*<<< orphan*/  widthLodError; } ;
typedef  TYPE_1__ srfBspSurface_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* Free ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void R_FreeSurfaceGridMeshData( srfBspSurface_t *grid ) {
	ri.Free(grid->widthLodError);
	ri.Free(grid->heightLodError);
	ri.Free(grid->indexes);
	ri.Free(grid->verts);
}