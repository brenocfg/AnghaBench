#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_21__ {scalar_t__ is_semi_transparent; scalar_t__ viewport_height; scalar_t__ viewport_width; } ;
struct TYPE_16__ {scalar_t__ is_focused; } ;
struct TYPE_20__ {TYPE_2__* grman; scalar_t__ lines; scalar_t__ columns; TYPE_13__ cursor_render_info; } ;
struct TYPE_19__ {scalar_t__ num_of_negative_refs; scalar_t__ count; } ;
struct TYPE_18__ {int /*<<< orphan*/  index; } ;
struct TYPE_17__ {TYPE_1__ render_data; } ;
typedef  TYPE_3__ Screen ;
typedef  TYPE_4__ OSWindow ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  int /*<<< orphan*/  GLint ;
typedef  float GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  CELL_BUFFERS ; 
 size_t CELL_PROGRAM ; 
 double OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_vao_uniform_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_vertex_array (int /*<<< orphan*/ ) ; 
 scalar_t__ ceilf (float) ; 
 TYPE_15__* cell_program_layouts ; 
 int /*<<< orphan*/  cell_update_uniform_block (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,float,float,float,float,TYPE_13__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  draw_cells_interleaved (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  draw_cells_interleaved_premult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  draw_cells_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int floorf (float) ; 
 int /*<<< orphan*/  glScissor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inactive_text_alpha ; 
 int screen_invert_colors (TYPE_3__*) ; 
 int /*<<< orphan*/  set_cell_uniforms (float) ; 
 int /*<<< orphan*/  uniform_buffer ; 

void
draw_cells(ssize_t vao_idx, ssize_t gvao_idx, GLfloat xstart, GLfloat ystart, GLfloat dx, GLfloat dy, Screen *screen, OSWindow *os_window, bool is_active_window, bool can_be_focused) {
    CELL_BUFFERS;
    bool inverted = screen_invert_colors(screen);

    cell_update_uniform_block(vao_idx, screen, uniform_buffer, xstart, ystart, dx, dy, &screen->cursor_render_info, inverted, os_window);

    bind_vao_uniform_buffer(vao_idx, uniform_buffer, cell_program_layouts[CELL_PROGRAM].render_data.index);
    bind_vertex_array(vao_idx);

    float current_inactive_text_alpha = (!can_be_focused || screen->cursor_render_info.is_focused) && is_active_window ? 1.0 : OPT(inactive_text_alpha);
    set_cell_uniforms(current_inactive_text_alpha);
    GLfloat w = (GLfloat)screen->columns * dx, h = (GLfloat)screen->lines * dy;
    // The scissor limits below are calculated to ensure that they do not
    // overlap with the pixels outside the draw area, see https://github.com/kovidgoyal/kitty/issues/741
    // for a test case (the scissor is also used by draw_cells_interleaved_premult to blit the framebuffer)
#define SCALE(w, x) ((GLfloat)(os_window->viewport_##w) * (GLfloat)(x))
    glScissor(
            (GLint)(ceilf(SCALE(width, (xstart + 1.0f) / 2.0f))),
            (GLint)(ceilf(SCALE(height, ((ystart - h) + 1.0f) / 2.0f))),
            (GLsizei)(floorf(SCALE(width, w / 2.0f))-1),
            (GLsizei)(floorf(SCALE(height, h / 2.0f))-1)
    );
#undef SCALE
    if (os_window->is_semi_transparent) {
        if (screen->grman->count) draw_cells_interleaved_premult(vao_idx, gvao_idx, screen, os_window);
        else draw_cells_simple(vao_idx, gvao_idx, screen);
    } else {
        if (screen->grman->num_of_negative_refs) draw_cells_interleaved(vao_idx, gvao_idx, screen);
        else draw_cells_simple(vao_idx, gvao_idx, screen);
    }
}