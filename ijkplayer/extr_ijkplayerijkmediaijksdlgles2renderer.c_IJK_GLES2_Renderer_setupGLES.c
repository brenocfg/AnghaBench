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
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  IJK_GLES2_checkError_TRACE (char*) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glCullFace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 

GLboolean IJK_GLES2_Renderer_setupGLES()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);       IJK_GLES2_checkError_TRACE("glClearColor");
    glEnable(GL_CULL_FACE);                     IJK_GLES2_checkError_TRACE("glEnable(GL_CULL_FACE)");
    glCullFace(GL_BACK);                        IJK_GLES2_checkError_TRACE("glCullFace");
    glDisable(GL_DEPTH_TEST);

    return GL_TRUE;
}