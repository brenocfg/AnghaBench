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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int color_type ;
struct TYPE_3__ {float background_opacity; scalar_t__ is_semi_transparent; } ;
typedef  TYPE_1__ OSWindow ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  BorderRect ;

/* Variables and functions */
 int /*<<< orphan*/  BORDERS_PROGRAM ; 
 size_t BORDER_active_border_color ; 
 size_t BORDER_background_opacity ; 
 size_t BORDER_bell_border_color ; 
 size_t BORDER_default_bg ; 
 size_t BORDER_inactive_border_color ; 
 size_t BORDER_viewport ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  GL_TRIANGLE_FAN ; 
 int /*<<< orphan*/  GL_WRITE_ONLY ; 
 int OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  active_border_color ; 
 void* alloc_and_map_vao_buffer (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  background ; 
 int /*<<< orphan*/  bell_border_color ; 
 int /*<<< orphan*/  bind_program (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_vertex_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * border_uniform_locations ; 
 int /*<<< orphan*/  glDrawArraysInstanced (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  glUniform1f (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  glUniform2ui (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform3f (int /*<<< orphan*/ ,float,float,float) ; 
 int /*<<< orphan*/  inactive_border_color ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  unbind_program () ; 
 int /*<<< orphan*/  unbind_vertex_array () ; 
 int /*<<< orphan*/  unmap_vao_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
draw_borders(ssize_t vao_idx, unsigned int num_border_rects, BorderRect *rect_buf, bool rect_data_is_dirty, uint32_t viewport_width, uint32_t viewport_height, color_type active_window_bg, unsigned int num_visible_windows, OSWindow *w) {
    if (num_border_rects) {
        if (rect_data_is_dirty) {
            size_t sz = sizeof(GLuint) * 5 * num_border_rects;
            void *borders_buf_address = alloc_and_map_vao_buffer(vao_idx, sz, 0, GL_STATIC_DRAW, GL_WRITE_ONLY);
            if (borders_buf_address) memcpy(borders_buf_address, rect_buf, sz);
            unmap_vao_buffer(vao_idx, 0);
        }
        bind_program(BORDERS_PROGRAM);
#define CV3(x) (((float)((x >> 16) & 0xff))/255.f), (((float)((x >> 8) & 0xff))/255.f), (((float)(x & 0xff))/255.f)
        glUniform1f(border_uniform_locations[BORDER_background_opacity], w->is_semi_transparent ? w->background_opacity : 1.0f);
        glUniform3f(border_uniform_locations[BORDER_active_border_color], CV3(OPT(active_border_color)));
        glUniform3f(border_uniform_locations[BORDER_inactive_border_color], CV3(OPT(inactive_border_color)));
        glUniform3f(border_uniform_locations[BORDER_bell_border_color], CV3(OPT(bell_border_color)));
        glUniform2ui(border_uniform_locations[BORDER_viewport], viewport_width, viewport_height);
        color_type default_bg = num_visible_windows > 1 ? OPT(background) : active_window_bg;
        glUniform3f(border_uniform_locations[BORDER_default_bg], CV3(default_bg));
#undef CV3
        bind_vertex_array(vao_idx);
        glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, num_border_rects);
        unbind_vertex_array();
        unbind_program();
    }
}