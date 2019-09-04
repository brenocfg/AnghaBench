#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t medium_font_idx; int /*<<< orphan*/  baseline; TYPE_1__* fonts; scalar_t__ fonts_count; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  face; } ;
typedef  TYPE_2__ StringCanvas ;
typedef  TYPE_3__ FontGroup ;
typedef  scalar_t__ FONTS_DATA_HANDLE ;

/* Variables and functions */
 TYPE_2__ render_simple_text_impl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

StringCanvas
render_simple_text(FONTS_DATA_HANDLE fg_, const char *text) {
    FontGroup *fg = (FontGroup*)fg_;
    if (fg->fonts_count && fg->medium_font_idx) return render_simple_text_impl(fg->fonts[fg->medium_font_idx].face, text, fg->baseline);
    StringCanvas ans = {0};
    return ans;
}