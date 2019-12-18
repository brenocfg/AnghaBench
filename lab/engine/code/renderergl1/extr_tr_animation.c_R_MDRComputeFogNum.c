#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_12__ {int frame; int /*<<< orphan*/  origin; } ;
struct TYPE_14__ {TYPE_2__ e; } ;
typedef  TYPE_4__ trRefEntity_t ;
struct TYPE_15__ {size_t numBones; int ofsFrames; } ;
typedef  TYPE_5__ mdrHeader_t ;
struct TYPE_16__ {scalar_t__ radius; int /*<<< orphan*/  localOrigin; int /*<<< orphan*/ * bones; } ;
typedef  TYPE_6__ mdrFrame_t ;
struct TYPE_17__ {scalar_t__** bounds; } ;
typedef  TYPE_7__ fog_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_11__ {int rdflags; } ;
struct TYPE_18__ {TYPE_3__* world; TYPE_1__ refdef; } ;
struct TYPE_13__ {int numfogs; TYPE_7__* fogs; } ;

/* Variables and functions */
 int RDF_NOWORLDMODEL ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_8__ tr ; 

int R_MDRComputeFogNum( mdrHeader_t *header, trRefEntity_t *ent ) {
	int				i, j;
	fog_t			*fog;
	mdrFrame_t		*mdrFrame;
	vec3_t			localOrigin;
	int frameSize;

	if ( tr.refdef.rdflags & RDF_NOWORLDMODEL ) {
		return 0;
	}
	
	frameSize = (size_t)( &((mdrFrame_t *)0)->bones[ header->numBones ] );

	// FIXME: non-normalized axis issues
	mdrFrame = ( mdrFrame_t * ) ( ( byte * ) header + header->ofsFrames + frameSize * ent->e.frame);
	VectorAdd( ent->e.origin, mdrFrame->localOrigin, localOrigin );
	for ( i = 1 ; i < tr.world->numfogs ; i++ ) {
		fog = &tr.world->fogs[i];
		for ( j = 0 ; j < 3 ; j++ ) {
			if ( localOrigin[j] - mdrFrame->radius >= fog->bounds[1][j] ) {
				break;
			}
			if ( localOrigin[j] + mdrFrame->radius <= fog->bounds[0][j] ) {
				break;
			}
		}
		if ( j == 3 ) {
			return i;
		}
	}

	return 0;
}