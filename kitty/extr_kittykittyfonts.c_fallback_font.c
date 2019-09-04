#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
struct TYPE_13__ {scalar_t__ debug_font_fallback; } ;
struct TYPE_12__ {int bold; int italic; int emoji_presentation; int /*<<< orphan*/  face; } ;
struct TYPE_11__ {size_t first_fallback_font_idx; size_t fallback_fonts_count; TYPE_3__* fonts; } ;
struct TYPE_10__ {int attrs; } ;
typedef  TYPE_1__ GPUCell ;
typedef  TYPE_2__ FontGroup ;
typedef  TYPE_3__ Font ;
typedef  int /*<<< orphan*/  CPUCell ;

/* Variables and functions */
 int BOLD_SHIFT ; 
 int ITALIC_SHIFT ; 
 TYPE_7__ global_state ; 
 scalar_t__ has_cell_text (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int has_emoji_presentation (int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t load_fallback_font (TYPE_2__*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  output_cell_fallback_data (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline ssize_t
fallback_font(FontGroup *fg, CPUCell *cpu_cell, GPUCell *gpu_cell) {
    bool bold = (gpu_cell->attrs >> BOLD_SHIFT) & 1;
    bool italic = (gpu_cell->attrs >> ITALIC_SHIFT) & 1;
    bool emoji_presentation = has_emoji_presentation(cpu_cell, gpu_cell);

    // Check if one of the existing fallback fonts has this text
    for (size_t i = 0, j = fg->first_fallback_font_idx; i < fg->fallback_fonts_count; i++, j++)  {
        Font *ff = fg->fonts +j;
        if (ff->bold == bold && ff->italic == italic && ff->emoji_presentation == emoji_presentation && has_cell_text(ff, cpu_cell)) {
            if (global_state.debug_font_fallback) output_cell_fallback_data(cpu_cell, bold, italic, emoji_presentation, ff->face, false);
            return j;
        }
    }

    return load_fallback_font(fg, cpu_cell, bold, italic, emoji_presentation);
}