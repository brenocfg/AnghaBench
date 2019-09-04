#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_symbol_fonts; scalar_t__ bi; scalar_t__ italic; scalar_t__ bold; } ;
struct TYPE_6__ {int fonts_capacity; int fonts_count; int bold_font_idx; int italic_font_idx; int bi_font_idx; int first_symbol_font_idx; int first_fallback_font_idx; scalar_t__ fallback_fonts_count; void* medium_font_idx; int /*<<< orphan*/ * fonts; } ;
typedef  TYPE_1__ FontGroup ;
typedef  int /*<<< orphan*/  Font ;

/* Variables and functions */
 int /*<<< orphan*/  calc_cell_metrics (TYPE_1__*) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 TYPE_4__ descriptor_indices ; 
 int /*<<< orphan*/  fatal (char*) ; 
 void* initialize_font (TYPE_1__*,scalar_t__,char*) ; 

__attribute__((used)) static void
initialize_font_group(FontGroup *fg) {
    fg->fonts_capacity = 10 + descriptor_indices.num_symbol_fonts;
    fg->fonts = calloc(fg->fonts_capacity, sizeof(Font));
    if (fg->fonts == NULL) fatal("Out of memory allocating fonts array");
    fg->fonts_count = 1;  // the 0 index font is the box font
#define I(attr)  if (descriptor_indices.attr) fg->attr##_font_idx = initialize_font(fg, descriptor_indices.attr, #attr); else fg->attr##_font_idx = -1;
    fg->medium_font_idx = initialize_font(fg, 0, "medium");
    I(bold); I(italic); I(bi);
#undef I
    fg->first_symbol_font_idx = fg->fonts_count; fg->first_fallback_font_idx = fg->fonts_count;
    fg->fallback_fonts_count = 0;
    for (size_t i = 0; i < descriptor_indices.num_symbol_fonts; i++) {
        initialize_font(fg, descriptor_indices.bi + 1 + i, "symbol_map");
        fg->first_fallback_font_idx++;
    }
#undef I
    calc_cell_metrics(fg);
}