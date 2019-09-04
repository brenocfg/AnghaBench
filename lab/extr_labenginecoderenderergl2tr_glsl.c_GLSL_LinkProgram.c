#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* Error ) (int /*<<< orphan*/ ,char*) ;} ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  GLSL_PRINTLOG_PROGRAM_INFO ; 
 int /*<<< orphan*/  GLSL_PrintLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qglGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qglLinkProgram (int /*<<< orphan*/ ) ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void GLSL_LinkProgram(GLuint program)
{
	GLint           linked;

	qglLinkProgram(program);

	qglGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(!linked)
	{
		GLSL_PrintLog(program, GLSL_PRINTLOG_PROGRAM_INFO, qfalse);
		ri.Error(ERR_DROP, "shaders failed to link");
	}
}