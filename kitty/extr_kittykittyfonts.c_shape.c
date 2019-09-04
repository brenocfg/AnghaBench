#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int index_type ;
typedef  int /*<<< orphan*/  hb_font_t ;
struct TYPE_7__ {int /*<<< orphan*/  current_codepoint; scalar_t__ codepoints_consumed; int /*<<< orphan*/  num_codepoints; int /*<<< orphan*/ * gpu_cell; TYPE_2__* cpu_cell; } ;
struct TYPE_9__ {int groups_capacity; int prev_was_special; int prev_was_empty; int num_cells; scalar_t__ num_glyphs; int /*<<< orphan*/  positions; int /*<<< orphan*/  info; int /*<<< orphan*/ * last_gpu_cell; TYPE_2__* last_cpu_cell; int /*<<< orphan*/ * first_gpu_cell; TYPE_2__* first_cpu_cell; scalar_t__ cell_idx; scalar_t__ glyph_idx; scalar_t__ group_idx; int /*<<< orphan*/  groups; TYPE_1__ current_cell_data; int /*<<< orphan*/  previous_cluster; } ;
struct TYPE_8__ {int /*<<< orphan*/  ch; } ;
typedef  int /*<<< orphan*/  Group ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  TYPE_2__ CPUCell ;

/* Variables and functions */
 int MAX (int,int) ; 
 scalar_t__ MIN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  fatal (char*) ; 
 TYPE_6__ group_state ; 
 int /*<<< orphan*/  harfbuzz_buffer ; 
 int /*<<< orphan*/  hb_buffer_get_glyph_infos (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  hb_buffer_get_glyph_positions (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  hb_shape (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  load_hb_buffer (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  no_calt_feature ; 
 int /*<<< orphan*/  num_codepoints_in_cell (TYPE_2__*) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
shape(CPUCell *first_cpu_cell, GPUCell *first_gpu_cell, index_type num_cells, hb_font_t *font, bool disable_ligature) {
    if (group_state.groups_capacity <= 2 * num_cells) {
        group_state.groups_capacity = MAX(128, 2 * num_cells);  // avoid unnecessary reallocs
        group_state.groups = realloc(group_state.groups, sizeof(Group) * group_state.groups_capacity);
        if (!group_state.groups) fatal("Out of memory");
    }
    group_state.previous_cluster = UINT32_MAX;
    group_state.prev_was_special = false;
    group_state.prev_was_empty = false;
    group_state.current_cell_data.cpu_cell = first_cpu_cell;
    group_state.current_cell_data.gpu_cell = first_gpu_cell;
    group_state.current_cell_data.num_codepoints = num_codepoints_in_cell(first_cpu_cell);
    group_state.current_cell_data.codepoints_consumed = 0;
    group_state.current_cell_data.current_codepoint = first_cpu_cell->ch;
    memset(group_state.groups, 0, sizeof(Group) * group_state.groups_capacity);
    group_state.group_idx = 0;
    group_state.glyph_idx = 0;
    group_state.cell_idx = 0;
    group_state.num_cells = num_cells;
    group_state.first_cpu_cell = first_cpu_cell;
    group_state.first_gpu_cell = first_gpu_cell;
    group_state.last_cpu_cell = first_cpu_cell + (num_cells ? num_cells - 1 : 0);
    group_state.last_gpu_cell = first_gpu_cell + (num_cells ? num_cells - 1 : 0);
    load_hb_buffer(first_cpu_cell, first_gpu_cell, num_cells);

    if (disable_ligature) {
        hb_shape(font, harfbuzz_buffer, &no_calt_feature, 1);
    } else {
        hb_shape(font, harfbuzz_buffer, NULL, 0);
    }

    unsigned int info_length, positions_length;
    group_state.info = hb_buffer_get_glyph_infos(harfbuzz_buffer, &info_length);
    group_state.positions = hb_buffer_get_glyph_positions(harfbuzz_buffer, &positions_length);
    if (!group_state.info || !group_state.positions) group_state.num_glyphs = 0;
    else group_state.num_glyphs = MIN(info_length, positions_length);
}