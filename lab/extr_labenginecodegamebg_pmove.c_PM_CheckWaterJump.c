#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {int waterlevel; int (* pointcontents ) (int*,int /*<<< orphan*/ ) ;TYPE_1__* ps; } ;
struct TYPE_5__ {int* forward; } ;
struct TYPE_4__ {int pm_time; int* velocity; int /*<<< orphan*/  pm_flags; int /*<<< orphan*/  clientNum; int /*<<< orphan*/  origin; } ;

/* Variables and functions */
 int CONTENTS_BODY ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SOLID ; 
 int /*<<< orphan*/  PMF_TIME_WATERJUMP ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorScale (int*,int,int*) ; 
 TYPE_3__* pm ; 
 TYPE_2__ pml ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int stub1 (int*,int /*<<< orphan*/ ) ; 
 int stub2 (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static qboolean	PM_CheckWaterJump( void ) {
	vec3_t	spot;
	int		cont;
	vec3_t	flatforward;

	if (pm->ps->pm_time) {
		return qfalse;
	}

	// check for water jump
	if ( pm->waterlevel != 2 ) {
		return qfalse;
	}

	flatforward[0] = pml.forward[0];
	flatforward[1] = pml.forward[1];
	flatforward[2] = 0;
	VectorNormalize (flatforward);

	VectorMA (pm->ps->origin, 30, flatforward, spot);
	spot[2] += 4;
	cont = pm->pointcontents (spot, pm->ps->clientNum );
	if ( !(cont & CONTENTS_SOLID) ) {
		return qfalse;
	}

	spot[2] += 16;
	cont = pm->pointcontents (spot, pm->ps->clientNum );
	if ( cont & (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_BODY) ) {
		return qfalse;
	}

	// jump out of water
	VectorScale (pml.forward, 200, pm->ps->velocity);
	pm->ps->velocity[2] = 350;

	pm->ps->pm_flags |= PMF_TIME_WATERJUMP;
	pm->ps->pm_time = 2000;

	return qtrue;
}