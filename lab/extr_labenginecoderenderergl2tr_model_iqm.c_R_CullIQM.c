#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec_t ;
typedef  scalar_t__* vec3_t ;
struct TYPE_8__ {int oldframe; int frame; } ;
struct TYPE_10__ {TYPE_1__ e; } ;
typedef  TYPE_3__ trRefEntity_t ;
struct TYPE_11__ {scalar_t__* bounds; } ;
typedef  TYPE_4__ iqmData_t ;
struct TYPE_9__ {int /*<<< orphan*/  c_box_cull_md3_out; int /*<<< orphan*/  c_box_cull_md3_clip; int /*<<< orphan*/  c_box_cull_md3_in; } ;
struct TYPE_12__ {TYPE_2__ pc; } ;

/* Variables and functions */
#define  CULL_CLIP 130 
#define  CULL_IN 129 
#define  CULL_OUT 128 
 int R_CullLocalBox (scalar_t__**) ; 
 TYPE_5__ tr ; 

__attribute__((used)) static int R_CullIQM( iqmData_t *data, trRefEntity_t *ent ) {
	vec3_t		bounds[2];
	vec_t		*oldBounds, *newBounds;
	int		i;

	if (!data->bounds) {
		tr.pc.c_box_cull_md3_clip++;
		return CULL_CLIP;
	}

	// compute bounds pointers
	oldBounds = data->bounds + 6*ent->e.oldframe;
	newBounds = data->bounds + 6*ent->e.frame;

	// calculate a bounding box in the current coordinate system
	for (i = 0 ; i < 3 ; i++) {
		bounds[0][i] = oldBounds[i] < newBounds[i] ? oldBounds[i] : newBounds[i];
		bounds[1][i] = oldBounds[i+3] > newBounds[i+3] ? oldBounds[i+3] : newBounds[i+3];
	}

	switch ( R_CullLocalBox( bounds ) )
	{
	case CULL_IN:
		tr.pc.c_box_cull_md3_in++;
		return CULL_IN;
	case CULL_CLIP:
		tr.pc.c_box_cull_md3_clip++;
		return CULL_CLIP;
	case CULL_OUT:
	default:
		tr.pc.c_box_cull_md3_out++;
		return CULL_OUT;
	}
}