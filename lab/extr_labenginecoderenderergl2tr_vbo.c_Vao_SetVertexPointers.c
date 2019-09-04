#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* attribs; } ;
typedef  TYPE_1__ vao_t ;
struct TYPE_8__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  stride; int /*<<< orphan*/  normalized; int /*<<< orphan*/  type; int /*<<< orphan*/  count; scalar_t__ enabled; } ;
typedef  TYPE_2__ vaoAttrib_t ;
typedef  int uint32_t ;
struct TYPE_11__ {scalar_t__ vertexArrayObject; } ;
struct TYPE_10__ {int vertexAttribsEnabled; } ;
struct TYPE_9__ {TYPE_1__* vao; } ;

/* Variables and functions */
 int ATTR_INDEX_COUNT ; 
 int /*<<< orphan*/  BUFFER_OFFSET (int /*<<< orphan*/ ) ; 
 TYPE_5__ glRefConfig ; 
 TYPE_4__ glState ; 
 int /*<<< orphan*/  qglDisableVertexAttribArray (int) ; 
 int /*<<< orphan*/  qglEnableVertexAttribArray (int) ; 
 int /*<<< orphan*/  qglVertexAttribPointer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ tess ; 

void Vao_SetVertexPointers(vao_t *vao)
{
	int attribIndex;

	// set vertex pointers
	for (attribIndex = 0; attribIndex < ATTR_INDEX_COUNT; attribIndex++)
	{
		uint32_t attribBit = 1 << attribIndex;
		vaoAttrib_t *vAtb = &vao->attribs[attribIndex];

		if (vAtb->enabled)
		{
			qglVertexAttribPointer(attribIndex, vAtb->count, vAtb->type, vAtb->normalized, vAtb->stride, BUFFER_OFFSET(vAtb->offset));
			if (glRefConfig.vertexArrayObject || !(glState.vertexAttribsEnabled & attribBit))
				qglEnableVertexAttribArray(attribIndex);

			if (!glRefConfig.vertexArrayObject || vao == tess.vao)
				glState.vertexAttribsEnabled |= attribBit;
		}
		else
		{
			// don't disable vertex attribs when using vertex array objects
			// Vao_SetVertexPointers is only called during init when using VAOs, and vertex attribs start disabled anyway
			if (!glRefConfig.vertexArrayObject && (glState.vertexAttribsEnabled & attribBit))
				qglDisableVertexAttribArray(attribIndex);

			if (!glRefConfig.vertexArrayObject || vao == tess.vao)
				glState.vertexAttribsEnabled &= ~attribBit;
		}
	}
}