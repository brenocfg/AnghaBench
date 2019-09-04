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
typedef  int /*<<< orphan*/  pixel ;
struct TYPE_5__ {size_t medium_font_idx; unsigned int cell_width; unsigned int cell_height; unsigned int baseline; unsigned int underline_position; unsigned int underline_thickness; int /*<<< orphan*/  canvas; int /*<<< orphan*/  sprite_tracker; TYPE_1__* fonts; } ;
struct TYPE_4__ {int /*<<< orphan*/  face; } ;
typedef  TYPE_2__ FontGroup ;

/* Variables and functions */
 int CELLS_IN_CANVAS ; 
 unsigned int MIN (unsigned int,unsigned int) ; 
 int OPT (int) ; 
 int adjust_column_width_frac ; 
 int adjust_column_width_px ; 
 int adjust_line_height_frac ; 
 int adjust_line_height_px ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  cell_metrics (int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int /*<<< orphan*/  sprite_tracker_set_layout (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void
calc_cell_metrics(FontGroup *fg) {
    unsigned int cell_height, cell_width, baseline, underline_position, underline_thickness;
    cell_metrics(fg->fonts[fg->medium_font_idx].face, &cell_width, &cell_height, &baseline, &underline_position, &underline_thickness);
    if (!cell_width) fatal("Failed to calculate cell width for the specified font");
    unsigned int before_cell_height = cell_height;
    int cw = cell_width, ch = cell_height;
    if (OPT(adjust_line_height_px) != 0) ch += OPT(adjust_line_height_px);
    if (OPT(adjust_line_height_frac) != 0.f) ch *= OPT(adjust_line_height_frac);
    if (OPT(adjust_column_width_px != 0)) cw += OPT(adjust_column_width_px);
    if (OPT(adjust_column_width_frac) != 0.f) cw *= OPT(adjust_column_width_frac);
#define MAX_DIM 1000
#define MIN_WIDTH 2
#define MIN_HEIGHT 4
    if (cw >= MIN_WIDTH && cw <= MAX_DIM) cell_width = cw;
    else log_error("Cell width invalid after adjustment, ignoring adjust_column_width");
    if (ch >= MIN_HEIGHT && ch <= MAX_DIM) cell_height = ch;
    else log_error("Cell height invalid after adjustment, ignoring adjust_line_height");
    int line_height_adjustment = cell_height - before_cell_height;
    if (cell_height < MIN_HEIGHT) fatal("Line height too small: %u", cell_height);
    if (cell_height > MAX_DIM) fatal("Line height too large: %u", cell_height);
    if (cell_width < MIN_WIDTH) fatal("Cell width too small: %u", cell_width);
    if (cell_width > MAX_DIM) fatal("Cell width too large: %u", cell_width);
#undef MIN_WIDTH
#undef MIN_HEIGHT
#undef MAX_DIM
    underline_position = MIN(cell_height - 1, underline_position);
    // ensure there is at least a couple of pixels available to render styled underlines
    while (underline_position > baseline + 1 && cell_height - underline_position < 2) underline_position--;
    if (line_height_adjustment > 1) {
        baseline += MIN(cell_height - 1, (unsigned)line_height_adjustment / 2);
        underline_position += MIN(cell_height - 1, (unsigned)line_height_adjustment / 2);
    }
    sprite_tracker_set_layout(&fg->sprite_tracker, cell_width, cell_height);
    fg->cell_width = cell_width; fg->cell_height = cell_height;
    fg->baseline = baseline; fg->underline_position = underline_position; fg->underline_thickness = underline_thickness;
    free(fg->canvas);
    fg->canvas = calloc(CELLS_IN_CANVAS * fg->cell_width * fg->cell_height, sizeof(pixel));
    if (!fg->canvas) fatal("Out of memory allocating canvas for font group");
}