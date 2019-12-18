#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {float* currentAngles; int /*<<< orphan*/  currentOrigin; int /*<<< orphan*/  bmodel; } ;
struct TYPE_6__ {TYPE_1__ r; } ;
typedef  TYPE_2__ sharedEntity_t ;
typedef  int /*<<< orphan*/  clipHandle_t ;

/* Variables and functions */
 int CM_PointContents (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int CM_TransformedPointContents (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 int MAX_GENTITIES ; 
 int SV_AreaEntities (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int*,int) ; 
 int /*<<< orphan*/  SV_ClipHandleForEntity (TYPE_2__*) ; 
 TYPE_2__* SV_GentityNum (int) ; 
 float* vec3_origin ; 

int SV_PointContents( const vec3_t p, int passEntityNum ) {
	int			touch[MAX_GENTITIES];
	sharedEntity_t *hit;
	int			i, num;
	int			contents, c2;
	clipHandle_t	clipHandle;
	float		*angles;

	// get base contents from world
	contents = CM_PointContents( p, 0 );

	// or in contents from all the other entities
	num = SV_AreaEntities( p, p, touch, MAX_GENTITIES );

	for ( i=0 ; i<num ; i++ ) {
		if ( touch[i] == passEntityNum ) {
			continue;
		}
		hit = SV_GentityNum( touch[i] );
		// might intersect, so do an exact clip
		clipHandle = SV_ClipHandleForEntity( hit );
		angles = hit->r.currentAngles;
		if ( !hit->r.bmodel ) {
			angles = vec3_origin;	// boxes don't rotate
		}

		c2 = CM_TransformedPointContents (p, clipHandle, hit->r.currentOrigin, angles);

		contents |= c2;
	}

	return contents;
}