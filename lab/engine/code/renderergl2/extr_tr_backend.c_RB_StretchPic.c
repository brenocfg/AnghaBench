#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  t2; int /*<<< orphan*/  s1; scalar_t__ h; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  s2; scalar_t__ w; int /*<<< orphan*/  t1; int /*<<< orphan*/ * shader; } ;
typedef  TYPE_1__ stretchPicCommand_t ;
typedef  int /*<<< orphan*/  shader_t ;
struct TYPE_10__ {int /*<<< orphan*/  color2D; int /*<<< orphan*/  entity2D; int /*<<< orphan*/ * currentEntity; scalar_t__ framePostProcessed; } ;
struct TYPE_9__ {scalar_t__ framebufferObject; } ;
struct TYPE_8__ {int numIndexes; int numVertexes; int* indexes; int /*<<< orphan*/ ** texCoords; scalar_t__** xyz; int /*<<< orphan*/ * color; int /*<<< orphan*/ * shader; } ;
struct TYPE_7__ {int /*<<< orphan*/ * renderFbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBO_Bind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_BeginSurface (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CHECKOVERFLOW (int,int) ; 
 int /*<<< orphan*/  RB_EndSurface () ; 
 int /*<<< orphan*/  RB_SetGL2D () ; 
 int /*<<< orphan*/  VectorCopy4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale4 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_5__ backEnd ; 
 TYPE_4__ glRefConfig ; 
 TYPE_3__ tess ; 
 TYPE_2__ tr ; 

const void *RB_StretchPic ( const void *data ) {
	const stretchPicCommand_t	*cmd;
	shader_t *shader;
	int		numVerts, numIndexes;

	cmd = (const stretchPicCommand_t *)data;

	// FIXME: HUGE hack
	if (glRefConfig.framebufferObject)
		FBO_Bind(backEnd.framePostProcessed ? NULL : tr.renderFbo);

	RB_SetGL2D();

	shader = cmd->shader;
	if ( shader != tess.shader ) {
		if ( tess.numIndexes ) {
			RB_EndSurface();
		}
		backEnd.currentEntity = &backEnd.entity2D;
		RB_BeginSurface( shader, 0, 0 );
	}

	RB_CHECKOVERFLOW( 4, 6 );
	numVerts = tess.numVertexes;
	numIndexes = tess.numIndexes;

	tess.numVertexes += 4;
	tess.numIndexes += 6;

	tess.indexes[ numIndexes ] = numVerts + 3;
	tess.indexes[ numIndexes + 1 ] = numVerts + 0;
	tess.indexes[ numIndexes + 2 ] = numVerts + 2;
	tess.indexes[ numIndexes + 3 ] = numVerts + 2;
	tess.indexes[ numIndexes + 4 ] = numVerts + 0;
	tess.indexes[ numIndexes + 5 ] = numVerts + 1;

	{
		uint16_t color[4];

		VectorScale4(backEnd.color2D, 257, color);

		VectorCopy4(color, tess.color[ numVerts ]);
		VectorCopy4(color, tess.color[ numVerts + 1]);
		VectorCopy4(color, tess.color[ numVerts + 2]);
		VectorCopy4(color, tess.color[ numVerts + 3 ]);
	}

	tess.xyz[ numVerts ][0] = cmd->x;
	tess.xyz[ numVerts ][1] = cmd->y;
	tess.xyz[ numVerts ][2] = 0;

	tess.texCoords[ numVerts ][0] = cmd->s1;
	tess.texCoords[ numVerts ][1] = cmd->t1;

	tess.xyz[ numVerts + 1 ][0] = cmd->x + cmd->w;
	tess.xyz[ numVerts + 1 ][1] = cmd->y;
	tess.xyz[ numVerts + 1 ][2] = 0;

	tess.texCoords[ numVerts + 1 ][0] = cmd->s2;
	tess.texCoords[ numVerts + 1 ][1] = cmd->t1;

	tess.xyz[ numVerts + 2 ][0] = cmd->x + cmd->w;
	tess.xyz[ numVerts + 2 ][1] = cmd->y + cmd->h;
	tess.xyz[ numVerts + 2 ][2] = 0;

	tess.texCoords[ numVerts + 2 ][0] = cmd->s2;
	tess.texCoords[ numVerts + 2 ][1] = cmd->t2;

	tess.xyz[ numVerts + 3 ][0] = cmd->x;
	tess.xyz[ numVerts + 3 ][1] = cmd->y + cmd->h;
	tess.xyz[ numVerts + 3 ][2] = 0;

	tess.texCoords[ numVerts + 3 ][0] = cmd->s1;
	tess.texCoords[ numVerts + 3 ][1] = cmd->t2;

	return (const void *)(cmd + 1);
}