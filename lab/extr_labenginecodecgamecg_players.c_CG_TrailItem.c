#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_6__ {int* origin; int /*<<< orphan*/  hModel; scalar_t__** axis; } ;
typedef  TYPE_1__ refEntity_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
typedef  int /*<<< orphan*/  ent ;
struct TYPE_7__ {int /*<<< orphan*/  lerpOrigin; int /*<<< orphan*/  lerpAngles; } ;
typedef  TYPE_2__ centity_t ;

/* Variables and functions */
 int /*<<< orphan*/  AnglesToAxis (scalar_t__*,scalar_t__**) ; 
 size_t PITCH ; 
 size_t ROLL ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,scalar_t__*,int*) ; 
 size_t YAW ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trap_R_AddRefEntityToScene (TYPE_1__*) ; 

__attribute__((used)) static void CG_TrailItem( centity_t *cent, qhandle_t hModel ) {
	refEntity_t		ent;
	vec3_t			angles;
	vec3_t			axis[3];

	VectorCopy( cent->lerpAngles, angles );
	angles[PITCH] = 0;
	angles[ROLL] = 0;
	AnglesToAxis( angles, axis );

	memset( &ent, 0, sizeof( ent ) );
	VectorMA( cent->lerpOrigin, -16, axis[0], ent.origin );
	ent.origin[2] += 16;
	angles[YAW] += 90;
	AnglesToAxis( angles, ent.axis );

	ent.hModel = hModel;
	trap_R_AddRefEntityToScene( &ent );
}