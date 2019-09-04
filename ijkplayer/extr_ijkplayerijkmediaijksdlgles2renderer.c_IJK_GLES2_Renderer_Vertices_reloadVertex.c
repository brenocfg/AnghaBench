#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  av4_position; int /*<<< orphan*/  vertices; } ;
typedef  TYPE_1__ IJK_GLES2_Renderer ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  IJK_GLES2_checkError_TRACE (char*) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void IJK_GLES2_Renderer_Vertices_reloadVertex(IJK_GLES2_Renderer *renderer)
{
    glVertexAttribPointer(renderer->av4_position, 2, GL_FLOAT, GL_FALSE, 0, renderer->vertices);    IJK_GLES2_checkError_TRACE("glVertexAttribPointer(av2_texcoord)");
    glEnableVertexAttribArray(renderer->av4_position);                                      IJK_GLES2_checkError_TRACE("glEnableVertexAttribArray(av2_texcoord)");
}