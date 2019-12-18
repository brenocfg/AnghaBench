#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ GLuint ;
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  IJK_GLES2_checkError (char*) ; 
 int /*<<< orphan*/  IJK_GLES2_checkError_TRACE (char*) ; 
 int /*<<< orphan*/  IJK_GLES2_printShaderInfo (scalar_t__) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  glCompileShader (scalar_t__) ; 
 scalar_t__ glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteShader (scalar_t__) ; 
 int /*<<< orphan*/  glGetShaderiv (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  glShaderSource (scalar_t__,int,char const**,int /*<<< orphan*/ *) ; 

GLuint IJK_GLES2_loadShader(GLenum shader_type, const char *shader_source)
{
    assert(shader_source);

    GLuint shader = glCreateShader(shader_type);        IJK_GLES2_checkError("glCreateShader");
    if (!shader)
        return 0;

    assert(shader_source);

    glShaderSource(shader, 1, &shader_source, NULL);    IJK_GLES2_checkError_TRACE("glShaderSource");
    glCompileShader(shader);                            IJK_GLES2_checkError_TRACE("glCompileShader");

    GLint compile_status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (!compile_status)
        goto fail;

    return shader;

fail:

    if (shader) {
        IJK_GLES2_printShaderInfo(shader);
        glDeleteShader(shader);
    }

    return 0;
}