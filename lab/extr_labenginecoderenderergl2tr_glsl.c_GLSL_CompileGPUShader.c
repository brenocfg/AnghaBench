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
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  GLchar ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  GLSL_PRINTLOG_SHADER_INFO ; 
 int /*<<< orphan*/  GLSL_PRINTLOG_SHADER_SOURCE ; 
 int /*<<< orphan*/  GLSL_PrintLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qglAttachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglCompileShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDeleteShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglDetachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qglGetShaderiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qglShaderSource (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const**,int*) ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int GLSL_CompileGPUShader(GLuint program, GLuint *prevShader, const GLchar *buffer, int size, GLenum shaderType)
{
	GLint           compiled;
	GLuint          shader;

	shader = qglCreateShader(shaderType);

	qglShaderSource(shader, 1, (const GLchar **)&buffer, &size);

	// compile shader
	qglCompileShader(shader);

	// check if shader compiled
	qglGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{
		GLSL_PrintLog(shader, GLSL_PRINTLOG_SHADER_SOURCE, qfalse);
		GLSL_PrintLog(shader, GLSL_PRINTLOG_SHADER_INFO, qfalse);
		ri.Error(ERR_DROP, "Couldn't compile shader");
		return 0;
	}

	if (*prevShader)
	{
		qglDetachShader(program, *prevShader);
		qglDeleteShader(*prevShader);
	}

	// attach shader to program
	qglAttachShader(program, shader);

	*prevShader = shader;

	return 1;
}