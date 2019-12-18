#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_7__ {double fraction; int /*<<< orphan*/  entityNum; } ;
typedef  TYPE_1__ trace_t ;
struct TYPE_8__ {int contentmask; scalar_t__* start; scalar_t__* end; scalar_t__* mins; scalar_t__* maxs; int passEntityNum; int capsule; scalar_t__* boxmins; scalar_t__* boxmaxs; TYPE_1__ trace; } ;
typedef  TYPE_2__ moveclip_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_BoxTrace (TYPE_1__*,scalar_t__* const,scalar_t__* const,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENTITYNUM_NONE ; 
 int /*<<< orphan*/  ENTITYNUM_WORLD ; 
 int /*<<< orphan*/  SV_ClipMoveToEntities (TYPE_2__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__* const,scalar_t__*) ; 
 scalar_t__* vec3_origin ; 

void SV_Trace( trace_t *results, const vec3_t start, vec3_t mins, vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask, int capsule ) {
	moveclip_t	clip;
	int			i;

	if ( !mins ) {
		mins = vec3_origin;
	}
	if ( !maxs ) {
		maxs = vec3_origin;
	}

	Com_Memset ( &clip, 0, sizeof ( moveclip_t ) );

	// clip to world
	CM_BoxTrace( &clip.trace, start, end, mins, maxs, 0, contentmask, capsule );
	clip.trace.entityNum = clip.trace.fraction != 1.0 ? ENTITYNUM_WORLD : ENTITYNUM_NONE;
	if ( clip.trace.fraction == 0 ) {
		*results = clip.trace;
		return;		// blocked immediately by the world
	}

	clip.contentmask = contentmask;
	clip.start = start;
//	VectorCopy( clip.trace.endpos, clip.end );
	VectorCopy( end, clip.end );
	clip.mins = mins;
	clip.maxs = maxs;
	clip.passEntityNum = passEntityNum;
	clip.capsule = capsule;

	// create the bounding box of the entire move
	// we can limit it to the part of the move not
	// already clipped off by the world, which can be
	// a significant savings for line of sight and shot traces
	for ( i=0 ; i<3 ; i++ ) {
		if ( end[i] > start[i] ) {
			clip.boxmins[i] = clip.start[i] + clip.mins[i] - 1;
			clip.boxmaxs[i] = clip.end[i] + clip.maxs[i] + 1;
		} else {
			clip.boxmins[i] = clip.end[i] + clip.mins[i] - 1;
			clip.boxmaxs[i] = clip.start[i] + clip.maxs[i] + 1;
		}
	}

	// clip to other solid entities
	SV_ClipMoveToEntities ( &clip );

	*results = clip.trace;
}