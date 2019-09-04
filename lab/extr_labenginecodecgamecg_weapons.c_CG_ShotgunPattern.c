#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_ShotgunPellet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DEFAULT_SHOTGUN_COUNT ; 
 int DEFAULT_SHOTGUN_SPREAD ; 
 int /*<<< orphan*/  PerpendicularVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Q_crandom (int*) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CG_ShotgunPattern( vec3_t origin, vec3_t origin2, int seed, int otherEntNum ) {
	int			i;
	float		r, u;
	vec3_t		end;
	vec3_t		forward, right, up;

	// derive the right and up vectors from the forward vector, because
	// the client won't have any other information
	VectorNormalize2( origin2, forward );
	PerpendicularVector( right, forward );
	CrossProduct( forward, right, up );

	// generate the "random" spread pattern
	for ( i = 0 ; i < DEFAULT_SHOTGUN_COUNT ; i++ ) {
		r = Q_crandom( &seed ) * DEFAULT_SHOTGUN_SPREAD * 16;
		u = Q_crandom( &seed ) * DEFAULT_SHOTGUN_SPREAD * 16;
		VectorMA( origin, 8192 * 16, forward, end);
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);

		CG_ShotgunPellet( origin, end, otherEntNum );
	}
}