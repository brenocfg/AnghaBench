#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  swapBuffersCommand_t ;
typedef  int /*<<< orphan*/  stretchPicCommand_t ;
typedef  int /*<<< orphan*/  shader_t ;
typedef  int /*<<< orphan*/  setColorCommand_t ;
struct TYPE_5__ {void* cmds; } ;
typedef  TYPE_1__ renderCommandList_t ;
struct TYPE_6__ {int numDrawSurfs; TYPE_3__* drawSurfs; } ;
typedef  TYPE_2__ drawSurfsCommand_t ;
struct TYPE_7__ {int sort; } ;
typedef  TYPE_3__ drawSurf_t ;
typedef  int /*<<< orphan*/  drawBufferCommand_t ;
struct TYPE_8__ {TYPE_1__ commands; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SHADERS ; 
 void* PADP (void const*,int) ; 
 int QSORT_FOGNUM_SHIFT ; 
 int QSORT_PSHADOW_SHIFT ; 
 int QSORT_SHADERNUM_SHIFT ; 
#define  RC_DRAW_BUFFER 133 
#define  RC_DRAW_SURFS 132 
#define  RC_END_OF_LIST 131 
#define  RC_SET_COLOR 130 
#define  RC_STRETCH_PIC 129 
#define  RC_SWAP_BUFFERS 128 
 int /*<<< orphan*/  R_DecomposeSort (int,int*,int /*<<< orphan*/ **,int*,int*,int*) ; 
 TYPE_4__* backEndData ; 

__attribute__((used)) static void FixRenderCommandList( int newShader ) {
	renderCommandList_t	*cmdList = &backEndData->commands;

	if( cmdList ) {
		const void *curCmd = cmdList->cmds;

		while ( 1 ) {
			curCmd = PADP(curCmd, sizeof(void *));

			switch ( *(const int *)curCmd ) {
			case RC_SET_COLOR:
				{
				const setColorCommand_t *sc_cmd = (const setColorCommand_t *)curCmd;
				curCmd = (const void *)(sc_cmd + 1);
				break;
				}
			case RC_STRETCH_PIC:
				{
				const stretchPicCommand_t *sp_cmd = (const stretchPicCommand_t *)curCmd;
				curCmd = (const void *)(sp_cmd + 1);
				break;
				}
			case RC_DRAW_SURFS:
				{
				int i;
				drawSurf_t	*drawSurf;
				shader_t	*shader;
				int			fogNum;
				int			entityNum;
				int			dlightMap;
				int         pshadowMap;
				int			sortedIndex;
				const drawSurfsCommand_t *ds_cmd =  (const drawSurfsCommand_t *)curCmd;

				for( i = 0, drawSurf = ds_cmd->drawSurfs; i < ds_cmd->numDrawSurfs; i++, drawSurf++ ) {
					R_DecomposeSort( drawSurf->sort, &entityNum, &shader, &fogNum, &dlightMap, &pshadowMap );
                    sortedIndex = (( drawSurf->sort >> QSORT_SHADERNUM_SHIFT ) & (MAX_SHADERS-1));
					if( sortedIndex >= newShader ) {
						sortedIndex++;
						drawSurf->sort = (sortedIndex << QSORT_SHADERNUM_SHIFT) | entityNum | ( fogNum << QSORT_FOGNUM_SHIFT ) | ( (int)pshadowMap << QSORT_PSHADOW_SHIFT) | (int)dlightMap;
					}
				}
				curCmd = (const void *)(ds_cmd + 1);
				break;
				}
			case RC_DRAW_BUFFER:
				{
				const drawBufferCommand_t *db_cmd = (const drawBufferCommand_t *)curCmd;
				curCmd = (const void *)(db_cmd + 1);
				break;
				}
			case RC_SWAP_BUFFERS:
				{
				const swapBuffersCommand_t *sb_cmd = (const swapBuffersCommand_t *)curCmd;
				curCmd = (const void *)(sb_cmd + 1);
				break;
				}
			case RC_END_OF_LIST:
			default:
				return;
			}
		}
	}
}