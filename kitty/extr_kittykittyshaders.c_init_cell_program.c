#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* stride; void* offset; void* size; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; int /*<<< orphan*/  size; } ;
struct TYPE_6__ {TYPE_2__ color_table; TYPE_1__ render_data; } ;

/* Variables and functions */
 int BORDERS_PROGRAM ; 
 int CELL_PROGRAM ; 
 int /*<<< orphan*/  GL_UNIFORM_ARRAY_STRIDE ; 
 int /*<<< orphan*/  GL_UNIFORM_OFFSET ; 
 int /*<<< orphan*/  GL_UNIFORM_SIZE ; 
 int attrib_location (int,char*) ; 
 int /*<<< orphan*/  blit_vertex_array ; 
 int /*<<< orphan*/  block_index (int,char*) ; 
 int /*<<< orphan*/  block_size (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* cell_program_layouts ; 
 int /*<<< orphan*/  create_vao () ; 
 int /*<<< orphan*/  fatal (char*,char*,int,int,int) ; 
 void* get_uniform_information (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenFramebuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  offscreen_framebuffer ; 

__attribute__((used)) static void
init_cell_program() {
    for (int i = CELL_PROGRAM; i < BORDERS_PROGRAM; i++) {
        cell_program_layouts[i].render_data.index = block_index(i, "CellRenderData");
        cell_program_layouts[i].render_data.size = block_size(i, cell_program_layouts[i].render_data.index);
        cell_program_layouts[i].color_table.size = get_uniform_information(i, "color_table[0]", GL_UNIFORM_SIZE);
        cell_program_layouts[i].color_table.offset = get_uniform_information(i, "color_table[0]", GL_UNIFORM_OFFSET);
        cell_program_layouts[i].color_table.stride = get_uniform_information(i, "color_table[0]", GL_UNIFORM_ARRAY_STRIDE);
    }
    // Sanity check to ensure the attribute location binding worked
#define C(p, name, expected) { int aloc = attrib_location(p, #name); if (aloc != expected && aloc != -1) fatal("The attribute location for %s is %d != %d in program: %d", #name, aloc, expected, p); }
    for (int p = CELL_PROGRAM; p < BORDERS_PROGRAM; p++) {
        C(p, colors, 0); C(p, sprite_coords, 1); C(p, is_selected, 2);
    }
#undef C
    glGenFramebuffers(1, &offscreen_framebuffer);
    blit_vertex_array = create_vao();
}