#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  srfVert_t ;
struct TYPE_3__ {int numVerts; int numIndexes; int /*<<< orphan*/ * indexes; int /*<<< orphan*/ * vertexes; } ;
typedef  TYPE_1__ queuedSurface_t ;
typedef  int /*<<< orphan*/  glIndex_t ;
struct TYPE_4__ {int numSurfaces; int vertexCommitSize; int indexCommitSize; TYPE_1__* surfaces; } ;

/* Variables and functions */
 TYPE_2__ vcq ; 

void VaoCache_AddSurface(srfVert_t *verts, int numVerts, glIndex_t *indexes, int numIndexes)
{
	queuedSurface_t *queueEntry = vcq.surfaces + vcq.numSurfaces;
	queueEntry->vertexes = verts;
	queueEntry->numVerts = numVerts;
	queueEntry->indexes = indexes;
	queueEntry->numIndexes = numIndexes;
	vcq.numSurfaces++;

	vcq.vertexCommitSize += sizeof(srfVert_t) * numVerts;
	vcq.indexCommitSize += sizeof(glIndex_t) * numIndexes;
}