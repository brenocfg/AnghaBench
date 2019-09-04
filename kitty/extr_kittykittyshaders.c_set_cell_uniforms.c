#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int constants_set; void* gploc; void* gpploc; void* cploc; void* cfploc; float prev_inactive_text_alpha; } ;

/* Variables and functions */
 int /*<<< orphan*/  CELL_FG_PROGRAM ; 
 int /*<<< orphan*/  CELL_PROGRAM ; 
 int /*<<< orphan*/  GRAPHICS_PREMULT_PROGRAM ; 
 int /*<<< orphan*/  GRAPHICS_PROGRAM ; 
 int /*<<< orphan*/  GRAPHICS_UNIT ; 
 float OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPRITE_MAP_UNIT ; 
 int /*<<< orphan*/  bind_program (int /*<<< orphan*/ ) ; 
 TYPE_1__ cell_uniform_data ; 
 int /*<<< orphan*/  dim_opacity ; 
 void* glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glUniform1f (void*,float) ; 
 int /*<<< orphan*/  glUniform1i (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
set_cell_uniforms(float current_inactive_text_alpha) {
    if (!cell_uniform_data.constants_set) {
        cell_uniform_data.gploc = glGetUniformLocation(program_id(GRAPHICS_PROGRAM), "inactive_text_alpha");
        cell_uniform_data.gpploc = glGetUniformLocation(program_id(GRAPHICS_PREMULT_PROGRAM), "inactive_text_alpha");
        cell_uniform_data.cploc = glGetUniformLocation(program_id(CELL_PROGRAM), "inactive_text_alpha");
        cell_uniform_data.cfploc = glGetUniformLocation(program_id(CELL_FG_PROGRAM), "inactive_text_alpha");
#define S(prog, name, val, type) { bind_program(prog); glUniform##type(glGetUniformLocation(program_id(prog), #name), val); }
        S(GRAPHICS_PROGRAM, image, GRAPHICS_UNIT, 1i);
        S(GRAPHICS_PREMULT_PROGRAM, image, GRAPHICS_UNIT, 1i);
        S(CELL_PROGRAM, sprites, SPRITE_MAP_UNIT, 1i); S(CELL_FG_PROGRAM, sprites, SPRITE_MAP_UNIT, 1i);
        S(CELL_PROGRAM, dim_opacity, OPT(dim_opacity), 1f); S(CELL_FG_PROGRAM, dim_opacity, OPT(dim_opacity), 1f);
#undef S
        cell_uniform_data.constants_set = true;
    }
    if (current_inactive_text_alpha != cell_uniform_data.prev_inactive_text_alpha) {
        cell_uniform_data.prev_inactive_text_alpha = current_inactive_text_alpha;
#define S(prog, loc) { bind_program(prog); glUniform1f(cell_uniform_data.loc, current_inactive_text_alpha); }
        S(CELL_PROGRAM, cploc); S(CELL_FG_PROGRAM, cfploc); S(GRAPHICS_PROGRAM, gploc); S(GRAPHICS_PREMULT_PROGRAM, gpploc);
#undef S
    }
}