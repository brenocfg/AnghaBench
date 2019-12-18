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
struct TYPE_5__ {int* uniforms; int /*<<< orphan*/  program; int /*<<< orphan*/  name; scalar_t__* uniformBufferOffsets; scalar_t__ uniformBuffer; } ;
typedef  TYPE_1__ shaderProgram_t ;
typedef  int /*<<< orphan*/  mat4_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  int GLint ;

/* Variables and functions */
 scalar_t__ GLSL_MAT16 ; 
 int /*<<< orphan*/  GL_FALSE ; 
 scalar_t__ Mat4Compare (int /*<<< orphan*/  const,float*) ; 
 int /*<<< orphan*/  Mat4Copy (int /*<<< orphan*/  const,float*) ; 
 int /*<<< orphan*/  PRINT_WARNING ; 
 int /*<<< orphan*/  qglProgramUniformMatrix4fvEXT (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 TYPE_3__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* uniformsInfo ; 

void GLSL_SetUniformMat4(shaderProgram_t *program, int uniformNum, const mat4_t matrix)
{
	GLint *uniforms = program->uniforms;
	vec_t *compare = (float *)(program->uniformBuffer + program->uniformBufferOffsets[uniformNum]);

	if (uniforms[uniformNum] == -1)
		return;

	if (uniformsInfo[uniformNum].type != GLSL_MAT16)
	{
		ri.Printf( PRINT_WARNING, "GLSL_SetUniformMat4: wrong type for uniform %i in program %s\n", uniformNum, program->name);
		return;
	}

	if (Mat4Compare(matrix, compare))
	{
		return;
	}

	Mat4Copy(matrix, compare);

	qglProgramUniformMatrix4fvEXT(program->program, uniforms[uniformNum], 1, GL_FALSE, matrix);
}