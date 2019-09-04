#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ index_type ;
typedef  int /*<<< orphan*/  glyph_index ;
typedef  int attrs_type ;
struct TYPE_20__ {char ch; } ;
struct TYPE_19__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_18__ {int /*<<< orphan*/  face; } ;
struct TYPE_17__ {float cell_width; TYPE_4__* fonts; } ;
struct TYPE_16__ {int attrs; int /*<<< orphan*/  decoration_fg; int /*<<< orphan*/  fg; } ;
struct TYPE_15__ {scalar_t__ xnum; TYPE_2__* gpu_cells; TYPE_6__* cpu_cells; } ;
typedef  TYPE_1__ Line ;
typedef  TYPE_2__ GPUCell ;
typedef  TYPE_3__ FontGroup ;
typedef  TYPE_4__ Font ;
typedef  scalar_t__ FONTS_DATA_HANDLE ;
typedef  scalar_t__ DisableLigature ;
typedef  TYPE_5__ Cursor ;
typedef  TYPE_6__ CPUCell ;

/* Variables and functions */
 scalar_t__ BOX_FONT ; 
 scalar_t__ DISABLE_LIGATURES_CURSOR ; 
 int MAX_NUM_EXTRA_GLYPHS_PUA ; 
 scalar_t__ MISSING_FONT ; 
 scalar_t__ NO_FONT ; 
 int WIDTH_MASK ; 
 int ceilf (float) ; 
 scalar_t__ font_for_cell (TYPE_3__*,TYPE_6__*,TYPE_2__*) ; 
 int get_glyph_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glyph_id_for_codepoint (int /*<<< orphan*/ ,char) ; 
 scalar_t__ is_private_use (char) ; 
 int /*<<< orphan*/  render_run (TYPE_3__*,TYPE_6__*,TYPE_2__*,scalar_t__,scalar_t__,int,int,int,scalar_t__) ; 

void
render_line(FONTS_DATA_HANDLE fg_, Line *line, index_type lnum, Cursor *cursor, DisableLigature disable_ligature_strategy) {
#define RENDER if (run_font_idx != NO_FONT && i > first_cell_in_run) { \
    int cursor_offset = -1; \
    if (disable_ligature_at_cursor && first_cell_in_run <= cursor->x && cursor->x <= i) cursor_offset = cursor->x - first_cell_in_run; \
    render_run(fg, line->cpu_cells + first_cell_in_run, line->gpu_cells + first_cell_in_run, i - first_cell_in_run, run_font_idx, false, center_glyph, cursor_offset, disable_ligature_strategy); \
}
    FontGroup *fg = (FontGroup*)fg_;
    ssize_t run_font_idx = NO_FONT;
    bool center_glyph = false;
    bool disable_ligature_at_cursor = cursor != NULL && disable_ligature_strategy == DISABLE_LIGATURES_CURSOR && lnum == cursor->y;
    index_type first_cell_in_run, i;
    attrs_type prev_width = 0;
    for (i=0, first_cell_in_run=0; i < line->xnum; i++) {
        if (prev_width == 2) { prev_width = 0; continue; }
        CPUCell *cpu_cell = line->cpu_cells + i;
        GPUCell *gpu_cell = line->gpu_cells + i;
        ssize_t cell_font_idx = font_for_cell(fg, cpu_cell, gpu_cell);

        if (is_private_use(cpu_cell->ch)
                && cell_font_idx != BOX_FONT
                && cell_font_idx != MISSING_FONT) {
            int desired_cells = 1;
            if (cell_font_idx > 0) {
                Font *font = (fg->fonts + cell_font_idx);
                glyph_index glyph_id = glyph_id_for_codepoint(font->face, cpu_cell->ch);

                int width = get_glyph_width(font->face, glyph_id);
                desired_cells = ceilf((float)width / fg->cell_width);
            }

            int num_spaces = 0;
            while ((line->cpu_cells[i+num_spaces+1].ch == ' ')
                    && num_spaces < MAX_NUM_EXTRA_GLYPHS_PUA
                    && num_spaces < desired_cells
                    && i + num_spaces + 1 < line->xnum) {
                num_spaces++;
                // We have a private use char followed by space(s), render it as a multi-cell ligature.
                GPUCell *space_cell = line->gpu_cells + i + num_spaces;
                // Ensure the space cell uses the foreground color from the PUA cell.
                // This is needed because there are applications like
                // Powerline that use PUA+space with different foreground colors
                // for the space and the PUA. See for example: https://github.com/kovidgoyal/kitty/issues/467
                space_cell->fg = gpu_cell->fg;
                space_cell->decoration_fg = gpu_cell->decoration_fg;
            }
            if (num_spaces) {
                center_glyph = true;
                RENDER
                center_glyph = false;
                render_run(fg, line->cpu_cells + i, line->gpu_cells + i, num_spaces + 1, cell_font_idx, true, center_glyph, -1, disable_ligature_strategy);
                run_font_idx = NO_FONT;
                first_cell_in_run = i + num_spaces + 1;
                prev_width = line->gpu_cells[i+num_spaces].attrs & WIDTH_MASK;
                i += num_spaces;
                continue;
            }
        }
        prev_width = gpu_cell->attrs & WIDTH_MASK;
        if (run_font_idx == NO_FONT) run_font_idx = cell_font_idx;
        if (run_font_idx == cell_font_idx) continue;
        RENDER
        run_font_idx = cell_font_idx;
        first_cell_in_run = i;
    }
    RENDER
#undef RENDER
}