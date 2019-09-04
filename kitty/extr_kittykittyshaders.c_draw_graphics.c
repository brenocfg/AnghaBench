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
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int group_count; int /*<<< orphan*/  texture_id; } ;
typedef  TYPE_1__ ImageRenderData ;
typedef  int GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TRIANGLE_FAN ; 
 scalar_t__ GRAPHICS_UNIT ; 
 int /*<<< orphan*/  bind_program (int) ; 
 int /*<<< orphan*/  bind_vertex_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glActiveTexture (scalar_t__) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
draw_graphics(int program, ssize_t vao_idx, ssize_t gvao_idx, ImageRenderData *data, GLuint start, GLuint count) {
    bind_program(program);
    bind_vertex_array(gvao_idx);
    glActiveTexture(GL_TEXTURE0 + GRAPHICS_UNIT);

    GLuint base = 4 * start;
    glEnable(GL_SCISSOR_TEST);
    for (GLuint i=0; i < count;) {
        ImageRenderData *rd = data + start + i;
        glBindTexture(GL_TEXTURE_2D, rd->texture_id);
        // You could reduce the number of draw calls by using
        // glDrawArraysInstancedBaseInstance but Apple chose to abandon OpenGL
        // before implementing it.
        for (GLuint k=0; k < rd->group_count; k++, base += 4, i++) glDrawArrays(GL_TRIANGLE_FAN, base, 4);
    }
    glDisable(GL_SCISSOR_TEST);
    bind_vertex_array(vao_idx);
}