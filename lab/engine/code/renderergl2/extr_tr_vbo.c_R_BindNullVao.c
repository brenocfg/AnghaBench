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
struct TYPE_4__ {scalar_t__ vertexArrayObject; } ;
struct TYPE_3__ {int /*<<< orphan*/ * currentVao; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_CheckErrors () ; 
 int /*<<< orphan*/  GL_ELEMENT_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GLimp_LogComment (char*) ; 
 TYPE_2__ glRefConfig ; 
 TYPE_1__ glState ; 
 int /*<<< orphan*/  qglBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglBindVertexArray (int /*<<< orphan*/ ) ; 

void R_BindNullVao(void)
{
	GLimp_LogComment("--- R_BindNullVao ---\n");

	if(glState.currentVao)
	{
		if (glRefConfig.vertexArrayObject)
		{
			qglBindVertexArray(0);

			// why you no save GL_ELEMENT_ARRAY_BUFFER binding, Intel?
			if (1) qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		else
		{
			qglBindBuffer(GL_ARRAY_BUFFER, 0);
			qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		glState.currentVao = NULL;
	}

	GL_CheckErrors();
}