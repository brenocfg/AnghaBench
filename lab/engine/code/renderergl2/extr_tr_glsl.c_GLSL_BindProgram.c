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
struct TYPE_7__ {char* name; int /*<<< orphan*/  program; } ;
typedef  TYPE_2__ shaderProgram_t ;
struct TYPE_6__ {int /*<<< orphan*/  c_glslShaderBinds; } ;
struct TYPE_9__ {TYPE_1__ pc; } ;
struct TYPE_8__ {scalar_t__ integer; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 scalar_t__ GL_UseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLimp_LogComment (int /*<<< orphan*/ ) ; 
 TYPE_4__ backEnd ; 
 TYPE_3__* r_logFile ; 
 int /*<<< orphan*/  va (char*,char*) ; 

void GLSL_BindProgram(shaderProgram_t * program)
{
	GLuint programObject = program ? program->program : 0;
	char *name = program ? program->name : "NULL";

	if(r_logFile->integer)
	{
		// don't just call LogComment, or we will get a call to va() every frame!
		GLimp_LogComment(va("--- GLSL_BindProgram( %s ) ---\n", name));
	}

	if (GL_UseProgram(programObject))
		backEnd.pc.c_glslShaderBinds++;
}