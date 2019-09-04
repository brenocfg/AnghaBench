#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
typedef  scalar_t__ surfaceType_t ;
struct TYPE_15__ {int /*<<< orphan*/  normal; } ;
struct TYPE_11__ {TYPE_8__ plane; } ;
struct TYPE_12__ {scalar_t__* data; TYPE_3__ cullinfo; TYPE_2__* shader; } ;
typedef  TYPE_4__ msurface_t ;
struct TYPE_13__ {int contents; int firstmarksurface; int nummarksurfaces; struct TYPE_13__** children; TYPE_8__* plane; } ;
typedef  TYPE_5__ mnode_t ;
struct TYPE_14__ {int viewCount; TYPE_1__* world; } ;
struct TYPE_10__ {int surfaceFlags; int contentFlags; } ;
struct TYPE_9__ {int* marksurfaces; int* surfacesViewCount; TYPE_4__* surfaces; } ;

/* Variables and functions */
 int BoxOnPlaneSide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int CONTENTS_FOG ; 
 double DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SF_FACE ; 
 scalar_t__ SF_GRID ; 
 scalar_t__ SF_TRIANGLES ; 
 int SURF_NOIMPACT ; 
 int SURF_NOMARKS ; 
 TYPE_6__ tr ; 

void R_BoxSurfaces_r(mnode_t *node, vec3_t mins, vec3_t maxs, surfaceType_t **list, int listsize, int *listlength, vec3_t dir) {

	int			s, c;
	msurface_t	*surf;
	int *mark;

	// do the tail recursion in a loop
	while ( node->contents == -1 ) {
		s = BoxOnPlaneSide( mins, maxs, node->plane );
		if (s == 1) {
			node = node->children[0];
		} else if (s == 2) {
			node = node->children[1];
		} else {
			R_BoxSurfaces_r(node->children[0], mins, maxs, list, listsize, listlength, dir);
			node = node->children[1];
		}
	}

	// add the individual surfaces
	mark = tr.world->marksurfaces + node->firstmarksurface;
	c = node->nummarksurfaces;
	while (c--) {
		int *surfViewCount;
		//
		if (*listlength >= listsize) break;
		//
		surfViewCount = &tr.world->surfacesViewCount[*mark];
		surf = tr.world->surfaces + *mark;
		// check if the surface has NOIMPACT or NOMARKS set
		if ( ( surf->shader->surfaceFlags & ( SURF_NOIMPACT | SURF_NOMARKS ) )
			|| ( surf->shader->contentFlags & CONTENTS_FOG ) ) {
			*surfViewCount = tr.viewCount;
		}
		// extra check for surfaces to avoid list overflows
		else if (*(surf->data) == SF_FACE) {
			// the face plane should go through the box
			s = BoxOnPlaneSide( mins, maxs, &surf->cullinfo.plane );
			if (s == 1 || s == 2) {
				*surfViewCount = tr.viewCount;
			} else if (DotProduct(surf->cullinfo.plane.normal, dir) > -0.5) {
			// don't add faces that make sharp angles with the projection direction
				*surfViewCount = tr.viewCount;
			}
		}
		else if (*(surf->data) != SF_GRID &&
			 *(surf->data) != SF_TRIANGLES)
			*surfViewCount = tr.viewCount;
		// check the viewCount because the surface may have
		// already been added if it spans multiple leafs
		if (*surfViewCount != tr.viewCount) {
			*surfViewCount = tr.viewCount;
			list[*listlength] = surf->data;
			(*listlength)++;
		}
		mark++;
	}
}