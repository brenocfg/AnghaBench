#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  index_type ;
typedef  int /*<<< orphan*/  glyph_index ;
struct TYPE_11__ {size_t glyph_idx; size_t num_glyphs; unsigned int cell_idx; unsigned int num_cells; int group_idx; int prev_was_empty; int prev_was_special; scalar_t__ previous_cluster; TYPE_2__* groups; int /*<<< orphan*/  last_cpu_cell; int /*<<< orphan*/  current_cell_data; TYPE_1__* info; } ;
struct TYPE_10__ {int /*<<< orphan*/  face; } ;
struct TYPE_9__ {int num_glyphs; int num_cells; int first_glyph_idx; unsigned int first_cell_idx; int has_special_glyph; } ;
struct TYPE_8__ {scalar_t__ cluster; int /*<<< orphan*/  codepoint; } ;
typedef  TYPE_2__ Group ;
typedef  int /*<<< orphan*/  GPUCell ;
typedef  TYPE_3__ Font ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 int MAX_NUM_EXTRA_GLYPHS ; 
 int MIN (unsigned int,int) ; 
 scalar_t__ UINT32_MAX ; 
 unsigned int check_cell_consumed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_7__ group_state ; 
 int /*<<< orphan*/  harfbuzz_font_for_face (int /*<<< orphan*/ ) ; 
 scalar_t__ is_empty_glyph (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int is_special_glyph (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shape (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
shape_run(CPUCell *first_cpu_cell, GPUCell *first_gpu_cell, index_type num_cells, Font *font, bool disable_ligature) {
    shape(first_cpu_cell, first_gpu_cell, num_cells, harfbuzz_font_for_face(font->face), disable_ligature);
#if 0
        // You can also generate this easily using hb-shape --show-extents --cluster-level=1 --shapers=ot /path/to/font/file text
        hb_buffer_serialize_glyphs(harfbuzz_buffer, 0, group_state.num_glyphs, (char*)canvas, sizeof(pixel) * CELLS_IN_CANVAS * cell_width * cell_height, NULL, harfbuzz_font_for_face(font->face), HB_BUFFER_SERIALIZE_FORMAT_TEXT, HB_BUFFER_SERIALIZE_FLAG_DEFAULT | HB_BUFFER_SERIALIZE_FLAG_GLYPH_EXTENTS);
        printf("\n%s\n", (char*)canvas);
        clear_canvas();
#endif
    /* Now distribute the glyphs into groups of cells
     * Considerations to keep in mind:
     * Group sizes should be as small as possible for best performance
     * Combining chars can result in multiple glyphs rendered into a single cell
     * Emoji and East Asian wide chars can cause a single glyph to be rendered over multiple cells
     * Ligature fonts, take two common approaches:
     * 1. ABC becomes EMPTY, EMPTY, WIDE GLYPH this means we have to render N glyphs in N cells (example Fira Code)
     * 2. ABC becomes WIDE GLYPH this means we have to render one glyph in N cells (example Operator Mono Lig)
     *
     * We rely on the cluster numbers from harfbuzz to tell us how many unicode codepoints a glyph corresponds to.
     * Then we check if the glyph is a ligature glyph (is_special_glyph) and if it is an empty glyph. These three
     * datapoints give us enough information to satisfy the constraint above, for a wide variety of fonts.
     */
    uint32_t cluster, next_cluster;
    bool add_to_current_group;
#define G(x) (group_state.x)
#define MAX_GLYPHS_IN_GROUP (MAX_NUM_EXTRA_GLYPHS + 1)
    while (G(glyph_idx) < G(num_glyphs) && G(cell_idx) < G(num_cells)) {
        glyph_index glyph_id = G(info)[G(glyph_idx)].codepoint;
        cluster = G(info)[G(glyph_idx)].cluster;
        bool is_special = is_special_glyph(glyph_id, font, &G(current_cell_data));
        bool is_empty = is_special && is_empty_glyph(glyph_id, font);
        uint32_t num_codepoints_used_by_glyph = 0;
        bool is_last_glyph = G(glyph_idx) == G(num_glyphs) - 1;
        Group *current_group = G(groups) + G(group_idx);
        if (is_last_glyph) {
            num_codepoints_used_by_glyph = UINT32_MAX;
        } else {
            next_cluster = G(info)[G(glyph_idx) + 1].cluster;
            // RTL languages like Arabic have decreasing cluster numbers
            if (next_cluster != cluster) num_codepoints_used_by_glyph = cluster > next_cluster ? cluster - next_cluster : next_cluster - cluster;
        }
        if (!current_group->num_glyphs) {
            add_to_current_group = true;
        } else {
            if (is_special) {
                add_to_current_group = G(prev_was_empty);
            } else {
                add_to_current_group = !G(prev_was_special);
            }
        }
        if (current_group->num_glyphs >= MAX_GLYPHS_IN_GROUP || current_group->num_cells >= MAX_GLYPHS_IN_GROUP) add_to_current_group = false;

        if (!add_to_current_group) { G(group_idx)++; current_group = G(groups) + G(group_idx); }
        if (!current_group->num_glyphs++) {
            current_group->first_glyph_idx = G(glyph_idx);
            current_group->first_cell_idx = G(cell_idx);
        }
#define MOVE_GLYPH_TO_NEXT_GROUP(start_cell_idx) { \
    current_group->num_glyphs--; \
    G(group_idx)++; current_group = G(groups) + G(group_idx); \
    current_group->first_cell_idx = start_cell_idx; \
    current_group->num_glyphs = 1; \
    current_group->first_glyph_idx = G(glyph_idx); \
}
        if (is_special) current_group->has_special_glyph = true;
        if (is_last_glyph) {
            // soak up all remaining cells
            if (G(cell_idx) < G(num_cells)) {
                unsigned int num_left = G(num_cells) - G(cell_idx);
                if (current_group->num_cells + num_left > MAX_GLYPHS_IN_GROUP) MOVE_GLYPH_TO_NEXT_GROUP(G(cell_idx));
                current_group->num_cells += num_left;
                if (current_group->num_cells > MAX_GLYPHS_IN_GROUP) current_group->num_cells = MAX_GLYPHS_IN_GROUP;  // leave any trailing cells empty
                G(cell_idx) += num_left;
            }
        } else {
            unsigned int num_cells_consumed = 0, start_cell_idx = G(cell_idx);
            while (num_codepoints_used_by_glyph && G(cell_idx) < G(num_cells)) {
                unsigned int w = check_cell_consumed(&G(current_cell_data), G(last_cpu_cell));
                G(cell_idx) += w;
                num_cells_consumed += w;
                num_codepoints_used_by_glyph--;
            }
            if (num_cells_consumed) {
                if (num_cells_consumed > MAX_GLYPHS_IN_GROUP) {
                    // Nasty, a single glyph used more than MAX_GLYPHS_IN_GROUP cells, we cannot render this case correctly
                    log_error("The glyph: %u needs more than %u cells, cannot render it", glyph_id, MAX_GLYPHS_IN_GROUP);
                    current_group->num_glyphs--;
                    while (num_cells_consumed) {
                        G(group_idx)++; current_group = G(groups) + G(group_idx);
                        current_group->num_glyphs = 1; current_group->first_glyph_idx = G(glyph_idx);
                        current_group->num_cells = MIN(num_cells_consumed, MAX_GLYPHS_IN_GROUP);
                        current_group->first_cell_idx = start_cell_idx;
                        start_cell_idx += current_group->num_cells;
                        num_cells_consumed -= current_group->num_cells;
                    }
                } else {
                    if (num_cells_consumed + current_group->num_cells > MAX_GLYPHS_IN_GROUP) MOVE_GLYPH_TO_NEXT_GROUP(start_cell_idx);
                    current_group->num_cells += num_cells_consumed;
                    if (!is_special) {  // not a ligature, end the group
                        G(group_idx)++; current_group = G(groups) + G(group_idx);
                    }
                }
            }
        }

        G(prev_was_special) = is_special;
        G(prev_was_empty) = is_empty;
        G(previous_cluster) = cluster;
        G(glyph_idx)++;
    }
#undef MOVE_GLYPH_TO_NEXT_GROUP
#undef MAX_GLYPHS_IN_GROUP
}