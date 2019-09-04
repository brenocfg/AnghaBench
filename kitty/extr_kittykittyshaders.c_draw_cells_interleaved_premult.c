#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_8__ {int /*<<< orphan*/  offscreen_texture_id; int /*<<< orphan*/  viewport_height; int /*<<< orphan*/  viewport_width; } ;
struct TYPE_7__ {int lines; int columns; TYPE_1__* grman; } ;
struct TYPE_6__ {scalar_t__ num_of_positive_refs; scalar_t__ num_of_negative_refs; int /*<<< orphan*/  render_data; } ;
typedef  TYPE_2__ Screen ;
typedef  TYPE_3__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  BLEND_PREMULT ; 
 int /*<<< orphan*/  BLIT_PROGRAM ; 
 scalar_t__ BLIT_UNIT ; 
 int /*<<< orphan*/  CELL_BG_PROGRAM ; 
 int /*<<< orphan*/  CELL_FG_PROGRAM ; 
 int /*<<< orphan*/  CELL_SPECIAL_PROGRAM ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_DRAW_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_SCISSOR_TEST ; 
 scalar_t__ GL_TEXTURE0 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  GL_TRIANGLE_FAN ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GRAPHICS_PREMULT_PROGRAM ; 
 int /*<<< orphan*/  bind_program (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_vertex_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blit_vertex_array ; 
 int /*<<< orphan*/  draw_graphics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  glActiveTexture (scalar_t__) ; 
 int /*<<< orphan*/  glBindFramebuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glDrawArraysInstanced (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFramebufferTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  offscreen_framebuffer ; 
 int /*<<< orphan*/  program_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
draw_cells_interleaved_premult(ssize_t vao_idx, ssize_t gvao_idx, Screen *screen, OSWindow *os_window) {
    if (!os_window->offscreen_texture_id) {
        glGenTextures(1, &os_window->offscreen_texture_id);
        glBindTexture(GL_TEXTURE_2D, os_window->offscreen_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, os_window->viewport_width, os_window->viewport_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, offscreen_framebuffer);
    glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, os_window->offscreen_texture_id, 0);
    /* if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) fatal("Offscreen framebuffer not complete"); */

    bind_program(CELL_BG_PROGRAM);
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, screen->lines * screen->columns);
    glEnable(GL_BLEND);
    BLEND_PREMULT;

    if (screen->grman->num_of_negative_refs) draw_graphics(GRAPHICS_PREMULT_PROGRAM, vao_idx, gvao_idx, screen->grman->render_data, 0, screen->grman->num_of_negative_refs);

    bind_program(CELL_SPECIAL_PROGRAM);
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, screen->lines * screen->columns);

    bind_program(CELL_FG_PROGRAM);
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, screen->lines * screen->columns);

    if (screen->grman->num_of_positive_refs) draw_graphics(GRAPHICS_PREMULT_PROGRAM, vao_idx, gvao_idx, screen->grman->render_data, screen->grman->num_of_negative_refs, screen->grman->num_of_positive_refs);

    glDisable(GL_BLEND);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    // Now render the framebuffer to the screen reversing alpha pre-multiplication
    glEnable(GL_SCISSOR_TEST);
    bind_program(BLIT_PROGRAM); bind_vertex_array(blit_vertex_array);
    static bool blit_constants_set = false;
    if (!blit_constants_set) {
        glUniform1i(glGetUniformLocation(program_id(BLIT_PROGRAM), "image"), BLIT_UNIT);
        blit_constants_set = true;
    }
    glActiveTexture(GL_TEXTURE0 + BLIT_UNIT);
    glBindTexture(GL_TEXTURE_2D, os_window->offscreen_texture_id);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisable(GL_SCISSOR_TEST);
}