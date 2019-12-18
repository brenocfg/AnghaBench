#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_9__ {int frame; int oldframe; int /*<<< orphan*/  nonNormalizedAxes; } ;
struct TYPE_11__ {TYPE_1__ e; } ;
typedef  TYPE_3__ trRefEntity_t ;
struct TYPE_12__ {int ofsFrames; } ;
typedef  TYPE_4__ md3Header_t ;
struct TYPE_13__ {scalar_t__** bounds; int /*<<< orphan*/  radius; int /*<<< orphan*/  localOrigin; } ;
typedef  TYPE_5__ md3Frame_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_10__ {int /*<<< orphan*/  c_box_cull_md3_out; int /*<<< orphan*/  c_box_cull_md3_clip; int /*<<< orphan*/  c_box_cull_md3_in; int /*<<< orphan*/  c_sphere_cull_md3_clip; int /*<<< orphan*/  c_sphere_cull_md3_in; int /*<<< orphan*/  c_sphere_cull_md3_out; } ;
struct TYPE_14__ {TYPE_2__ pc; } ;

/* Variables and functions */
#define  CULL_CLIP 130 
#define  CULL_IN 129 
#define  CULL_OUT 128 
 int R_CullLocalBox (scalar_t__**) ; 
 int R_CullLocalPointAndRadius (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ tr ; 

__attribute__((used)) static int R_CullModel( md3Header_t *header, trRefEntity_t *ent ) {
	vec3_t		bounds[2];
	md3Frame_t	*oldFrame, *newFrame;
	int			i;

	// compute frame pointers
	newFrame = ( md3Frame_t * ) ( ( byte * ) header + header->ofsFrames ) + ent->e.frame;
	oldFrame = ( md3Frame_t * ) ( ( byte * ) header + header->ofsFrames ) + ent->e.oldframe;

	// cull bounding sphere ONLY if this is not an upscaled entity
	if ( !ent->e.nonNormalizedAxes )
	{
		if ( ent->e.frame == ent->e.oldframe )
		{
			switch ( R_CullLocalPointAndRadius( newFrame->localOrigin, newFrame->radius ) )
			{
			case CULL_OUT:
				tr.pc.c_sphere_cull_md3_out++;
				return CULL_OUT;

			case CULL_IN:
				tr.pc.c_sphere_cull_md3_in++;
				return CULL_IN;

			case CULL_CLIP:
				tr.pc.c_sphere_cull_md3_clip++;
				break;
			}
		}
		else
		{
			int sphereCull, sphereCullB;

			sphereCull  = R_CullLocalPointAndRadius( newFrame->localOrigin, newFrame->radius );
			if ( newFrame == oldFrame ) {
				sphereCullB = sphereCull;
			} else {
				sphereCullB = R_CullLocalPointAndRadius( oldFrame->localOrigin, oldFrame->radius );
			}

			if ( sphereCull == sphereCullB )
			{
				if ( sphereCull == CULL_OUT )
				{
					tr.pc.c_sphere_cull_md3_out++;
					return CULL_OUT;
				}
				else if ( sphereCull == CULL_IN )
				{
					tr.pc.c_sphere_cull_md3_in++;
					return CULL_IN;
				}
				else
				{
					tr.pc.c_sphere_cull_md3_clip++;
				}
			}
		}
	}
	
	// calculate a bounding box in the current coordinate system
	for (i = 0 ; i < 3 ; i++) {
		bounds[0][i] = oldFrame->bounds[0][i] < newFrame->bounds[0][i] ? oldFrame->bounds[0][i] : newFrame->bounds[0][i];
		bounds[1][i] = oldFrame->bounds[1][i] > newFrame->bounds[1][i] ? oldFrame->bounds[1][i] : newFrame->bounds[1][i];
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