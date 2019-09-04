#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  srfVert_t ;
struct TYPE_7__ {scalar_t__ indexes; int numIndexes; int numVerts; int /*<<< orphan*/  vertexes; } ;
typedef  TYPE_1__ queuedSurface_t ;
typedef  int /*<<< orphan*/  glIndex_t ;
struct TYPE_8__ {scalar_t__ data; int size; int bufferOffset; } ;
typedef  TYPE_2__ buffered_t ;
struct TYPE_12__ {int /*<<< orphan*/  indexesIBO; int /*<<< orphan*/  vertexesVBO; } ;
struct TYPE_11__ {int firstIndex; } ;
struct TYPE_10__ {int* batchLengths; int numBatches; int numSurfaces; int indexOffset; int vertexOffset; TYPE_6__* vao; TYPE_2__* surfaceIndexSets; } ;
struct TYPE_9__ {int numSurfaces; int vertexCommitSize; int indexCommitSize; int /*<<< orphan*/ * indexes; int /*<<< orphan*/ * vertexes; TYPE_1__* surfaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  R_BindVao (TYPE_6__*) ; 
 int /*<<< orphan*/  qglBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglBufferSubData (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 TYPE_5__ tess ; 
 TYPE_4__ vc ; 
 TYPE_3__ vcq ; 

void VaoCache_Commit(void)
{
	buffered_t *indexSet;
	int *batchLength;
	queuedSurface_t *surf, *end = vcq.surfaces + vcq.numSurfaces;

	R_BindVao(vc.vao);

	// Search for a matching batch
	// FIXME: Use faster search
	indexSet = vc.surfaceIndexSets;
	batchLength = vc.batchLengths;
	for (; batchLength < vc.batchLengths + vc.numBatches; batchLength++)
	{
		if (*batchLength == vcq.numSurfaces)
		{
			buffered_t *indexSet2 = indexSet;
			for (surf = vcq.surfaces; surf < end; surf++, indexSet2++)
			{
				if (surf->indexes != indexSet2->data || (surf->numIndexes * sizeof(glIndex_t)) != indexSet2->size)
					break;
			}

			if (surf == end)
				break;
		}

		indexSet += *batchLength;
	}

	// If found, use it
	if (indexSet < vc.surfaceIndexSets + vc.numSurfaces)
	{
		tess.firstIndex = indexSet->bufferOffset / sizeof(glIndex_t);
		//ri.Printf(PRINT_ALL, "firstIndex %d numIndexes %d as %d\n", tess.firstIndex, tess.numIndexes, (int)(batchLength - vc.batchLengths));
		//ri.Printf(PRINT_ALL, "vc.numSurfaces %d vc.numBatches %d\n", vc.numSurfaces, vc.numBatches);
	}
	// If not, rebuffer the batch
	// FIXME: keep track of the vertexes so we don't have to reupload them every time
	else
	{
		srfVert_t *dstVertex = vcq.vertexes;
		glIndex_t *dstIndex = vcq.indexes;

		batchLength = vc.batchLengths + vc.numBatches;
		*batchLength = vcq.numSurfaces;
		vc.numBatches++;

		tess.firstIndex = vc.indexOffset / sizeof(glIndex_t);
		vcq.vertexCommitSize = 0;
		vcq.indexCommitSize = 0;
		for (surf = vcq.surfaces; surf < end; surf++)
		{
			glIndex_t *srcIndex = surf->indexes;
			int vertexesSize = surf->numVerts * sizeof(srfVert_t);
			int indexesSize = surf->numIndexes * sizeof(glIndex_t);
			int i, indexOffset = (vc.vertexOffset + vcq.vertexCommitSize) / sizeof(srfVert_t);

			Com_Memcpy(dstVertex, surf->vertexes, vertexesSize);
			dstVertex += surf->numVerts;

			vcq.vertexCommitSize += vertexesSize;

			indexSet = vc.surfaceIndexSets + vc.numSurfaces;
			indexSet->data = surf->indexes;
			indexSet->size = indexesSize;
			indexSet->bufferOffset = vc.indexOffset + vcq.indexCommitSize;
			vc.numSurfaces++;

			for (i = 0; i < surf->numIndexes; i++)
				*dstIndex++ = *srcIndex++ + indexOffset;

			vcq.indexCommitSize += indexesSize;
		}

		//ri.Printf(PRINT_ALL, "committing %d to %d, %d to %d as %d\n", vcq.vertexCommitSize, vc.vertexOffset, vcq.indexCommitSize, vc.indexOffset, (int)(batchLength - vc.batchLengths));

		if (vcq.vertexCommitSize)
		{
			qglBindBuffer(GL_ARRAY_BUFFER, vc.vao->vertexesVBO);
			qglBufferSubData(GL_ARRAY_BUFFER, vc.vertexOffset, vcq.vertexCommitSize, vcq.vertexes);
			vc.vertexOffset += vcq.vertexCommitSize;
		}

		if (vcq.indexCommitSize)
		{
			qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vc.vao->indexesIBO);
			qglBufferSubData(GL_ELEMENT_ARRAY_BUFFER, vc.indexOffset, vcq.indexCommitSize, vcq.indexes);
			vc.indexOffset += vcq.indexCommitSize;
		}
	}
}