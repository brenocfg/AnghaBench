#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int vec_t ;
typedef  int* vec3_t ;
struct TYPE_11__ {int frame; int /*<<< orphan*/  origin; } ;
struct TYPE_13__ {TYPE_2__ e; } ;
typedef  TYPE_4__ trRefEntity_t ;
struct TYPE_14__ {int* bounds; } ;
typedef  TYPE_5__ iqmData_t ;
struct TYPE_15__ {int** bounds; } ;
typedef  TYPE_6__ fog_t ;
struct TYPE_10__ {int rdflags; } ;
struct TYPE_16__ {TYPE_3__* world; TYPE_1__ refdef; } ;
struct TYPE_12__ {int numfogs; TYPE_6__* fogs; } ;

/* Variables and functions */
 int RDF_NOWORLDMODEL ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int*,int*) ; 
 float VectorLength (int*) ; 
 int /*<<< orphan*/  VectorMA (int const*,float,int*,int*) ; 
 int /*<<< orphan*/  VectorSubtract (int const*,int const*,int*) ; 
 TYPE_7__ tr ; 

int R_ComputeIQMFogNum( iqmData_t *data, trRefEntity_t *ent ) {
	int			i, j;
	fog_t			*fog;
	const vec_t		*bounds;
	const vec_t		defaultBounds[6] = { -8, -8, -8, 8, 8, 8 };
	vec3_t			diag, center;
	vec3_t			localOrigin;
	vec_t			radius;

	if ( tr.refdef.rdflags & RDF_NOWORLDMODEL ) {
		return 0;
	}

	// FIXME: non-normalized axis issues
	if (data->bounds) {
		bounds = data->bounds + 6*ent->e.frame;
	} else {
		bounds = defaultBounds;
	}
	VectorSubtract( bounds+3, bounds, diag );
	VectorMA( bounds, 0.5f, diag, center );
	VectorAdd( ent->e.origin, center, localOrigin );
	radius = 0.5f * VectorLength( diag );

	for ( i = 1 ; i < tr.world->numfogs ; i++ ) {
		fog = &tr.world->fogs[i];
		for ( j = 0 ; j < 3 ; j++ ) {
			if ( localOrigin[j] - radius >= fog->bounds[1][j] ) {
				break;
			}
			if ( localOrigin[j] + radius <= fog->bounds[0][j] ) {
				break;
			}
		}
		if ( j == 3 ) {
			return i;
		}
	}

	return 0;
}