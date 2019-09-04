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
struct TYPE_3__ {int height; int width; int /*<<< orphan*/ * verts; } ;
typedef  TYPE_1__ mesh_t ;
typedef  int /*<<< orphan*/  bspDrawVert_t ;

/* Variables and functions */

void InvertMesh( mesh_t *in ) {
	int w, h;
	bspDrawVert_t temp;

	for ( h = 0 ; h < in->height ; h++ ) {
		for ( w = 0 ; w < in->width / 2 ; w++ ) {
			temp = in->verts[ h * in->width + w ];
			in->verts[ h * in->width + w ] = in->verts[ h * in->width + in->width - 1 - w ];
			in->verts[ h * in->width + in->width - 1 - w ] = temp;
		}
	}
}