#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ uniformBuffer; scalar_t__ program; scalar_t__ fragmentShader; scalar_t__ vertexShader; } ;
typedef  TYPE_1__ shaderProgram_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* Free ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qglDeleteProgram (scalar_t__) ; 
 int /*<<< orphan*/  qglDeleteShader (scalar_t__) ; 
 int /*<<< orphan*/  qglDetachShader (scalar_t__,scalar_t__) ; 
 TYPE_2__ ri ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

void GLSL_DeleteGPUShader(shaderProgram_t *program)
{
	if(program->program)
	{
		if (program->vertexShader)
		{
			qglDetachShader(program->program, program->vertexShader);
			qglDeleteShader(program->vertexShader);
		}

		if (program->fragmentShader)
		{
			qglDetachShader(program->program, program->fragmentShader);
			qglDeleteShader(program->fragmentShader);
		}

		qglDeleteProgram(program->program);

		if (program->uniformBuffer)
		{
			ri.Free(program->uniformBuffer);
		}

		Com_Memset(program, 0, sizeof(*program));
	}
}