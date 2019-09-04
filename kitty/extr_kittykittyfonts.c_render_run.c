#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  scalar_t__ index_type ;
struct TYPE_5__ {int /*<<< orphan*/ * fonts; } ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  TYPE_1__ FontGroup ;
typedef  int /*<<< orphan*/  DisableLigature ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
#define  BLANK_FONT 130 
#define  BOX_FONT 129 
 int /*<<< orphan*/  DISABLE_LIGATURES_ALWAYS ; 
#define  MISSING_FONT 128 
 int /*<<< orphan*/  MISSING_GLYPH ; 
 int /*<<< orphan*/  merge_groups_for_pua_space_ligature () ; 
 int /*<<< orphan*/  render_box_cell (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  render_groups (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shape_run (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  split_run_at_offset (int,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static inline void
render_run(FontGroup *fg, CPUCell *first_cpu_cell, GPUCell *first_gpu_cell, index_type num_cells, ssize_t font_idx, bool pua_space_ligature, bool center_glyph, int cursor_offset, DisableLigature disable_ligature_strategy) {
    switch(font_idx) {
        default:
            shape_run(first_cpu_cell, first_gpu_cell, num_cells, &fg->fonts[font_idx], disable_ligature_strategy == DISABLE_LIGATURES_ALWAYS);
            if (pua_space_ligature) merge_groups_for_pua_space_ligature();
            else if (cursor_offset > -1) {
                index_type left, right;
                split_run_at_offset(cursor_offset, &left, &right);
                if (right > left) {
                    if (left) {
                        shape_run(first_cpu_cell, first_gpu_cell, left, &fg->fonts[font_idx], false);
                        render_groups(fg, &fg->fonts[font_idx], center_glyph);
                    }
                        shape_run(first_cpu_cell + left, first_gpu_cell + left, right - left, &fg->fonts[font_idx], true);
                        render_groups(fg, &fg->fonts[font_idx], center_glyph);
                    if (right < num_cells) {
                        shape_run(first_cpu_cell + right, first_gpu_cell + right, num_cells - right, &fg->fonts[font_idx], false);
                        render_groups(fg, &fg->fonts[font_idx], center_glyph);
                    }
                    break;
                }
            }
            render_groups(fg, &fg->fonts[font_idx], center_glyph);
            break;
        case BLANK_FONT:
            while(num_cells--) { set_sprite(first_gpu_cell, 0, 0, 0); first_cpu_cell++; first_gpu_cell++; }
            break;
        case BOX_FONT:
            while(num_cells--) { render_box_cell(fg, first_cpu_cell, first_gpu_cell); first_cpu_cell++; first_gpu_cell++; }
            break;
        case MISSING_FONT:
            while(num_cells--) { set_sprite(first_gpu_cell, MISSING_GLYPH, 0, 0); first_cpu_cell++; first_gpu_cell++; }
            break;
    }
}