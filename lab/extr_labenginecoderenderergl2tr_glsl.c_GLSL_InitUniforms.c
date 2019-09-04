#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
struct TYPE_6__ {int* uniforms; int* uniformBufferOffsets; int /*<<< orphan*/  uniformBuffer; int /*<<< orphan*/  program; } ;
typedef  TYPE_1__ shaderProgram_t ;
struct TYPE_9__ {int glslMaxAnimatedBones; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* Malloc ) (int) ;} ;
struct TYPE_7__ {int type; int /*<<< orphan*/  name; } ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLfloat ;

/* Variables and functions */
#define  GLSL_FLOAT 135 
#define  GLSL_FLOAT5 134 
#define  GLSL_INT 133 
#define  GLSL_MAT16 132 
#define  GLSL_MAT16_BONEMATRIX 131 
#define  GLSL_VEC2 130 
#define  GLSL_VEC3 129 
#define  GLSL_VEC4 128 
 int UNIFORM_COUNT ; 
 TYPE_4__ glRefConfig ; 
 int qglGetUniformLocation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ ri ; 
 int /*<<< orphan*/  stub1 (int) ; 
 TYPE_2__* uniformsInfo ; 

void GLSL_InitUniforms(shaderProgram_t *program)
{
	int i, size;

	GLint *uniforms = program->uniforms;

	size = 0;
	for (i = 0; i < UNIFORM_COUNT; i++)
	{
		uniforms[i] = qglGetUniformLocation(program->program, uniformsInfo[i].name);

		if (uniforms[i] == -1)
			continue;
		 
		program->uniformBufferOffsets[i] = size;

		switch(uniformsInfo[i].type)
		{
			case GLSL_INT:
				size += sizeof(GLint);
				break;
			case GLSL_FLOAT:
				size += sizeof(GLfloat);
				break;
			case GLSL_FLOAT5:
				size += sizeof(vec_t) * 5;
				break;
			case GLSL_VEC2:
				size += sizeof(vec_t) * 2;
				break;
			case GLSL_VEC3:
				size += sizeof(vec_t) * 3;
				break;
			case GLSL_VEC4:
				size += sizeof(vec_t) * 4;
				break;
			case GLSL_MAT16:
				size += sizeof(vec_t) * 16;
				break;
			case GLSL_MAT16_BONEMATRIX:
				size += sizeof(vec_t) * 16 * glRefConfig.glslMaxAnimatedBones;
				break;
			default:
				break;
		}
	}

	program->uniformBuffer = ri.Malloc(size);
}