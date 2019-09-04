#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {int lines; int columns; TYPE_1__* grman; } ;
struct TYPE_4__ {scalar_t__ count; int /*<<< orphan*/  render_data; } ;
typedef  TYPE_2__ Screen ;

/* Variables and functions */
 int /*<<< orphan*/  BLEND_ONTO_OPAQUE ; 
 int /*<<< orphan*/  CELL_PROGRAM ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_TRIANGLE_FAN ; 
 int /*<<< orphan*/  GRAPHICS_PROGRAM ; 
 int /*<<< orphan*/  bind_program (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_graphics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDrawArraysInstanced (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
draw_cells_simple(ssize_t vao_idx, ssize_t gvao_idx, Screen *screen) {
    bind_program(CELL_PROGRAM);
    glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, screen->lines * screen->columns);
    if (screen->grman->count) {
        glEnable(GL_BLEND);
        BLEND_ONTO_OPAQUE;
        draw_graphics(GRAPHICS_PROGRAM, vao_idx, gvao_idx, screen->grman->render_data, 0, screen->grman->count);
        glDisable(GL_BLEND);
    }
}