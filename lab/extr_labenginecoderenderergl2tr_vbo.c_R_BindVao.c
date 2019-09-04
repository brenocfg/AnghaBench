#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  indexesIBO; int /*<<< orphan*/  vertexesVBO; int /*<<< orphan*/  vao; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ vao_t ;
struct TYPE_11__ {int /*<<< orphan*/  c_vaoBinds; } ;
struct TYPE_18__ {TYPE_1__ pc; } ;
struct TYPE_17__ {scalar_t__ intelGraphics; scalar_t__ vertexArrayObject; } ;
struct TYPE_16__ {int /*<<< orphan*/  vertexAnimation; scalar_t__ vertexAttribsInterpolation; TYPE_2__* currentVao; } ;
struct TYPE_15__ {scalar_t__ integer; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_13__ {TYPE_2__* vao; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GLimp_LogComment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vao_SetVertexPointers (TYPE_2__*) ; 
 TYPE_8__ backEnd ; 
 TYPE_7__ glRefConfig ; 
 TYPE_6__ glState ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qglBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglBindVertexArray (int /*<<< orphan*/ ) ; 
 TYPE_5__* r_logFile ; 
 TYPE_4__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ tess ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

void R_BindVao(vao_t * vao)
{
	if(!vao)
	{
		//R_BindNullVao();
		ri.Error(ERR_DROP, "R_BindVao: NULL vao");
		return;
	}

	if(r_logFile->integer)
	{
		// don't just call LogComment, or we will get a call to va() every frame!
		GLimp_LogComment(va("--- R_BindVao( %s ) ---\n", vao->name));
	}

	if(glState.currentVao != vao)
	{
		glState.currentVao = vao;

		glState.vertexAttribsInterpolation = 0;
		glState.vertexAnimation = qfalse;
		backEnd.pc.c_vaoBinds++;

		if (glRefConfig.vertexArrayObject)
		{
			qglBindVertexArray(vao->vao);

			// Intel Graphics doesn't save GL_ELEMENT_ARRAY_BUFFER binding with VAO binding.
			if (glRefConfig.intelGraphics || vao == tess.vao)
				qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->indexesIBO);

			// tess VAO always has buffers bound
			if (vao == tess.vao)
				qglBindBuffer(GL_ARRAY_BUFFER, vao->vertexesVBO);
		}
		else
		{
			qglBindBuffer(GL_ARRAY_BUFFER, vao->vertexesVBO);
			qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->indexesIBO);

			// tess VAO doesn't have vertex pointers set until data is uploaded
			if (vao != tess.vao)
				Vao_SetVertexPointers(vao);
		}
	}
}