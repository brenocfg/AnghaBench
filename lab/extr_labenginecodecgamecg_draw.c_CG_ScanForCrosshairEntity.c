#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_13__ {size_t entityNum; int /*<<< orphan*/  endpos; } ;
typedef  TYPE_5__ trace_t ;
struct TYPE_12__ {int /*<<< orphan*/ * viewaxis; int /*<<< orphan*/  vieworg; } ;
struct TYPE_15__ {size_t crosshairClientNum; int /*<<< orphan*/  time; int /*<<< orphan*/  crosshairClientTime; TYPE_2__* snap; TYPE_4__ refdef; } ;
struct TYPE_11__ {int powerups; } ;
struct TYPE_14__ {TYPE_3__ currentState; } ;
struct TYPE_9__ {int /*<<< orphan*/  clientNum; } ;
struct TYPE_10__ {TYPE_1__ ps; } ;

/* Variables and functions */
 int CG_PointContents (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_Trace (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CONTENTS_BODY ; 
 int CONTENTS_FOG ; 
 int CONTENTS_SOLID ; 
 size_t MAX_CLIENTS ; 
 int PW_INVIS ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ cg ; 
 TYPE_6__* cg_entities ; 
 int /*<<< orphan*/  vec3_origin ; 

__attribute__((used)) static void CG_ScanForCrosshairEntity( void ) {
	trace_t		trace;
	vec3_t		start, end;
	int			content;

	VectorCopy( cg.refdef.vieworg, start );
	VectorMA( start, 131072, cg.refdef.viewaxis[0], end );

	CG_Trace( &trace, start, vec3_origin, vec3_origin, end, 
		cg.snap->ps.clientNum, CONTENTS_SOLID|CONTENTS_BODY );
	if ( trace.entityNum >= MAX_CLIENTS ) {
		return;
	}

	// if the player is in fog, don't show it
	content = CG_PointContents( trace.endpos, 0 );
	if ( content & CONTENTS_FOG ) {
		return;
	}

	// if the player is invisible, don't show it
	if ( cg_entities[ trace.entityNum ].currentState.powerups & ( 1 << PW_INVIS ) ) {
		return;
	}

	// update the fade timer
	cg.crosshairClientNum = trace.entityNum;
	cg.crosshairClientTime = cg.time;
}