#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  float vec_t ;
typedef  int /*<<< orphan*/ * vec4_t ;
struct TYPE_5__ {int* uniforms; int /*<<< orphan*/  program; int /*<<< orphan*/  name; scalar_t__* uniformBufferOffsets; scalar_t__ uniformBuffer; } ;
typedef  TYPE_1__ shaderProgram_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  int GLint ;

/* Variables and functions */
 scalar_t__ GLSL_VEC4 ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 scalar_t__ VectorCompare4 (int /*<<< orphan*/ * const,float*) ; 
 int /*<<< orphan*/  VectorCopy4 (int /*<<< orphan*/ * const,float*) ; 
 int /*<<< orphan*/  qglProgramUniform4fEXT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* uniformsInfo ; 

void GLSL_SetUniformVec4(shaderProgram_t *program, int uniformNum, const vec4_t v)
{
	GLint *uniforms = program->uniforms;
	vec_t *compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (uniformsInfo[uniformNum].type != GLSL_VEC4)
	{
		ri.Printf( PRINT_WARNING, "GLSL_SetUniformVec4: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (VectorCompare4(v, compare))
	{
		return;
	}

	VectorCopy4(v, compare);

	qglProgramUniform4fEXT(program->program, uniforms[uniformNum], v[0], v[1], v[2], v[3]);
}