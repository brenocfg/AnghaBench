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
struct TYPE_4__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/ * depthBlurShader; int /*<<< orphan*/  ssaoShader; int /*<<< orphan*/  shadowmaskShader; int /*<<< orphan*/ * calclevels4xShader; int /*<<< orphan*/  tonemapShader; int /*<<< orphan*/  bokehShader; int /*<<< orphan*/  down4xShader; int /*<<< orphan*/  pshadowShader; int /*<<< orphan*/ * shadowmapShader; int /*<<< orphan*/ * lightallShader; int /*<<< orphan*/ * dlightShader; int /*<<< orphan*/ * fogShader; int /*<<< orphan*/  textureColorShader; int /*<<< orphan*/ * genericShader; } ;

/* Variables and functions */
 int ATTR_INDEX_COUNT ; 
 int DLIGHTDEF_COUNT ; 
 int FOGDEF_COUNT ; 
 int GENERICDEF_COUNT ; 
 int /*<<< orphan*/  GLSL_DeleteGPUShader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GL_BindNullProgram () ; 
 int LIGHTDEF_COUNT ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int SHADOWMAPDEF_COUNT ; 
 int /*<<< orphan*/  qglDisableVertexAttribArray (int) ; 
 TYPE_2__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ tr ; 

void GLSL_ShutdownGPUShaders(void)
{
	int i;

	ri.Printf(PRINT_ALL, "------- GLSL_ShutdownGPUShaders -------\n");

	for (i = 0; i < ATTR_INDEX_COUNT; i++)
		qglDisableVertexAttribArray(i);

	GL_BindNullProgram();

	for ( i = 0; i < GENERICDEF_COUNT; i++)
		GLSL_DeleteGPUShader(&tr.genericShader[i]);

	GLSL_DeleteGPUShader(&tr.textureColorShader);

	for ( i = 0; i < FOGDEF_COUNT; i++)
		GLSL_DeleteGPUShader(&tr.fogShader[i]);

	for ( i = 0; i < DLIGHTDEF_COUNT; i++)
		GLSL_DeleteGPUShader(&tr.dlightShader[i]);

	for ( i = 0; i < LIGHTDEF_COUNT; i++)
		GLSL_DeleteGPUShader(&tr.lightallShader[i]);

	for ( i = 0; i < SHADOWMAPDEF_COUNT; i++)
		GLSL_DeleteGPUShader(&tr.shadowmapShader[i]);

	GLSL_DeleteGPUShader(&tr.pshadowShader);
	GLSL_DeleteGPUShader(&tr.down4xShader);
	GLSL_DeleteGPUShader(&tr.bokehShader);
	GLSL_DeleteGPUShader(&tr.tonemapShader);

	for ( i = 0; i < 2; i++)
		GLSL_DeleteGPUShader(&tr.calclevels4xShader[i]);

	GLSL_DeleteGPUShader(&tr.shadowmaskShader);
	GLSL_DeleteGPUShader(&tr.ssaoShader);

	for ( i = 0; i < 4; i++)
		GLSL_DeleteGPUShader(&tr.depthBlurShader[i]);
}