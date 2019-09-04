#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_10__ {unsigned int cell_width; unsigned int cell_height; } ;
struct TYPE_7__ {unsigned int width; unsigned int height; } ;
struct TYPE_9__ {int /*<<< orphan*/  gvao_idx; TYPE_5__* fonts_data; TYPE_1__ live_resize; } ;
struct TYPE_8__ {scalar_t__ canvas; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ StringCanvas ;
typedef  TYPE_3__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  draw_centered_alpha_mask (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 TYPE_2__ render_simple_text (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void
draw_resizing_text(OSWindow *w) {
    char text[32] = {0};
    unsigned int width = w->live_resize.width, height = w->live_resize.height;
    snprintf(text, sizeof(text), "%u x %u cells", width / w->fonts_data->cell_width, height / w->fonts_data->cell_height);
    StringCanvas rendered = render_simple_text(w->fonts_data, text);
    if (rendered.canvas) {
        draw_centered_alpha_mask(w->gvao_idx, width, height, rendered.width, rendered.height, rendered.canvas);
        free(rendered.canvas);
    }
}