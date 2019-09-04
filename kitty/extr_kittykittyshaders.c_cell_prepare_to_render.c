#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_10__ {int /*<<< orphan*/  render_data; int /*<<< orphan*/  count; } ;
struct TYPE_9__ {scalar_t__ last_rendered_cursor_x; scalar_t__ last_rendered_cursor_y; int lines; int columns; TYPE_6__* grman; int /*<<< orphan*/  cell_size; int /*<<< orphan*/  scrolled_by; TYPE_1__* cursor; scalar_t__ is_dirty; scalar_t__ scroll_changed; int /*<<< orphan*/  disable_ligatures; } ;
struct TYPE_8__ {scalar_t__ x; scalar_t__ y; } ;
typedef  TYPE_2__ Screen ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  int /*<<< orphan*/  GLfloat ;
typedef  int /*<<< orphan*/  FONTS_DATA_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CELL_BUFFERS ; 
 int /*<<< orphan*/  DISABLE_LIGATURES_CURSOR ; 
 int /*<<< orphan*/  GL_STREAM_DRAW ; 
 int /*<<< orphan*/  GL_WRITE_ONLY ; 
 void* alloc_and_map_vao_buffer (scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cell_data_buffer ; 
 int /*<<< orphan*/  ensure_sprite_map (int /*<<< orphan*/ ) ; 
 scalar_t__ grman_update_layers (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_apply_selection (TYPE_2__*,void*,size_t) ; 
 scalar_t__ screen_is_selection_dirty (TYPE_2__*) ; 
 int /*<<< orphan*/  screen_update_cell_data (TYPE_2__*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  selection_buffer ; 
 int /*<<< orphan*/  send_graphics_data_to_gpu (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_vao_buffer (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
cell_prepare_to_render(ssize_t vao_idx, ssize_t gvao_idx, Screen *screen, GLfloat xstart, GLfloat ystart, GLfloat dx, GLfloat dy, FONTS_DATA_HANDLE fonts_data) {
    size_t sz;
    CELL_BUFFERS;
    void *address;
    bool changed = false;

    ensure_sprite_map(fonts_data);

    bool cursor_pos_changed = screen->cursor->x != screen->last_rendered_cursor_x
                           || screen->cursor->y != screen->last_rendered_cursor_y;
    bool disable_ligatures = screen->disable_ligatures == DISABLE_LIGATURES_CURSOR;

    if (screen->scroll_changed || screen->is_dirty || (disable_ligatures && cursor_pos_changed)) {
        sz = sizeof(GPUCell) * screen->lines * screen->columns;
        address = alloc_and_map_vao_buffer(vao_idx, sz, cell_data_buffer, GL_STREAM_DRAW, GL_WRITE_ONLY);
        screen_update_cell_data(screen, address, fonts_data, disable_ligatures && cursor_pos_changed);
        unmap_vao_buffer(vao_idx, cell_data_buffer); address = NULL;
        changed = true;
    }

    if (cursor_pos_changed) {
        screen->last_rendered_cursor_x = screen->cursor->x;
        screen->last_rendered_cursor_y = screen->cursor->y;
    }

    if (screen_is_selection_dirty(screen)) {
        sz = screen->lines * screen->columns;
        address = alloc_and_map_vao_buffer(vao_idx, sz, selection_buffer, GL_STREAM_DRAW, GL_WRITE_ONLY);
        screen_apply_selection(screen, address, sz);
        unmap_vao_buffer(vao_idx, selection_buffer); address = NULL;
        changed = true;
    }

    if (gvao_idx && grman_update_layers(screen->grman, screen->scrolled_by, xstart, ystart, dx, dy, screen->columns, screen->lines, screen->cell_size)) {
        send_graphics_data_to_gpu(screen->grman->count, gvao_idx, screen->grman->render_data);
        changed = true;
    }
    return changed;
}