#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec3_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {scalar_t__ origin; } ;

/* Variables and functions */
 float DistanceSquared (scalar_t__,int /*<<< orphan*/ ) ; 
 float THIRD_PERSON_THRESHOLD_SQ ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__,scalar_t__) ; 
 int listener_number ; 
 int /*<<< orphan*/  listener_origin ; 
 TYPE_1__* loopSounds ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean S_Base_HearingThroughEntity( int entityNum, vec3_t origin )
{
	float	distanceSq;
	vec3_t	sorigin;

	if (origin)
		VectorCopy(origin, sorigin);
	else
		VectorCopy(loopSounds[entityNum].origin, sorigin);

	if( listener_number == entityNum )
	{
		// This is an outrageous hack to detect
		// whether or not the player is rendering in third person or not. We can't
		// ask the renderer because the renderer has no notion of entities and we
		// can't ask cgame since that would involve changing the API and hence mod
		// compatibility. I don't think there is any way around this, but I'll leave
		// the FIXME just in case anyone has a bright idea.
		distanceSq = DistanceSquared(
				sorigin,
				listener_origin );

		if( distanceSq > THIRD_PERSON_THRESHOLD_SQ )
			return qfalse; //we're the player, but third person
		else
			return qtrue;  //we're the player
	}
	else
		return qfalse; //not the player
}