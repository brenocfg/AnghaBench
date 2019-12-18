#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct status_block {scalar_t__ sep_block_width; } ;
struct TYPE_6__ {int /*<<< orphan*/  statusline_buffer; } ;
typedef  TYPE_1__ i3_output ;
typedef  int /*<<< orphan*/  color_t ;
struct TYPE_9__ {int /*<<< orphan*/  bar_bg; int /*<<< orphan*/  focus_bar_bg; int /*<<< orphan*/  sep_fg; int /*<<< orphan*/  focus_sep_fg; } ;
struct TYPE_8__ {int /*<<< orphan*/ * separator_symbol; } ;
struct TYPE_7__ {int height; } ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * TAILQ_NEXT (struct status_block*,int /*<<< orphan*/ ) ; 
 int bar_height ; 
 int /*<<< orphan*/  blocks ; 
 TYPE_5__ colors ; 
 TYPE_4__ config ; 
 int /*<<< orphan*/  draw_util_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  draw_util_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 
 TYPE_2__ font ; 
 scalar_t__ get_sep_offset (struct status_block*) ; 
 int logical_px (int) ; 
 int sep_voff_px ; 
 int separator_symbol_width ; 

__attribute__((used)) static void draw_separator(i3_output *output, uint32_t x, struct status_block *block, bool use_focus_colors) {
    color_t sep_fg = (use_focus_colors ? colors.focus_sep_fg : colors.sep_fg);
    color_t bar_bg = (use_focus_colors ? colors.focus_bar_bg : colors.bar_bg);

    uint32_t sep_offset = get_sep_offset(block);
    if (TAILQ_NEXT(block, blocks) == NULL || sep_offset == 0)
        return;

    uint32_t center_x = x - sep_offset;
    if (config.separator_symbol == NULL) {
        /* Draw a classic one pixel, vertical separator. */
        draw_util_rectangle(&output->statusline_buffer, sep_fg,
                            center_x,
                            logical_px(sep_voff_px),
                            logical_px(1),
                            bar_height - 2 * logical_px(sep_voff_px));
    } else {
        /* Draw a custom separator. */
        uint32_t separator_x = MAX(x - block->sep_block_width, center_x - separator_symbol_width / 2);
        draw_util_text(config.separator_symbol, &output->statusline_buffer, sep_fg, bar_bg,
                       separator_x, bar_height / 2 - font.height / 2, x - separator_x);
    }
}