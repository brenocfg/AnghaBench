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
typedef  float* vec3_t ;
typedef  int /*<<< orphan*/  team_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {int /*<<< orphan*/  angles; int /*<<< orphan*/  origin; } ;
struct TYPE_7__ {float randomAngleRange; TYPE_1__ s; } ;
typedef  TYPE_2__ gentity_t ;

/* Variables and functions */
 TYPE_2__* SelectRandomTeamSpawnPoint (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* SelectSpawnPoint (int /*<<< orphan*/ ,float*,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,float*) ; 
 float random () ; 
 int /*<<< orphan*/  vec3_origin ; 

gentity_t *SelectCTFSpawnPoint ( team_t team, int teamstate, vec3_t origin, vec3_t angles, qboolean isbot ) {
	gentity_t	*spot;

	spot = SelectRandomTeamSpawnPoint ( teamstate, team, isbot );

	if (!spot) {
		return SelectSpawnPoint( vec3_origin, origin, angles, isbot );
	}

	VectorCopy(spot->s.origin, origin);
	origin[2] += 9.0f;
	VectorCopy(spot->s.angles, angles);
	if ( spot->randomAngleRange == 360.0f ) {
		angles[1] = random() * 360.0f;
	} else {
		// Pick random orientation within segment: angles[1] +/- 0.5 * segment.
		float segment = ( random() - 0.5f ) * spot->randomAngleRange;
		angles[1] += segment;
	}

	return spot;
}