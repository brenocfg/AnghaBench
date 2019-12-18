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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int width; scalar_t__ height; } ;
struct TYPE_8__ {int /*<<< orphan*/  surface; TYPE_1__ dims; } ;
typedef  TYPE_3__ dialog_t ;
typedef  int /*<<< orphan*/  color_t ;
struct TYPE_7__ {scalar_t__ height; } ;
struct TYPE_9__ {TYPE_2__ font; } ;

/* Variables and functions */
 scalar_t__ backtrace_done ; 
 int border_width ; 
 TYPE_5__ config ; 
 int /*<<< orphan*/  draw_util_clear_surface (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const draw_util_hex_to_color (char*) ; 
 int /*<<< orphan*/  draw_util_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  draw_util_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int const,int,int const) ; 
 int margin ; 
 int /*<<< orphan*/  message_intro ; 
 int /*<<< orphan*/  message_intro2 ; 
 int /*<<< orphan*/  message_option_backtrace ; 
 int /*<<< orphan*/  message_option_forget ; 
 int /*<<< orphan*/  message_option_restart ; 

__attribute__((used)) static void sighandler_draw_dialog(dialog_t *dialog) {
    const color_t black = draw_util_hex_to_color("#000000");
    const color_t white = draw_util_hex_to_color("#FFFFFF");
    const color_t red = draw_util_hex_to_color("#FF0000");

    /* Start with a clean slate and draw a red border. */
    draw_util_clear_surface(&(dialog->surface), red);
    draw_util_rectangle(&(dialog->surface), black, border_width, border_width,
                        dialog->dims.width - 2 * border_width, dialog->dims.height - 2 * border_width);

    int y = border_width + margin;
    const int x = border_width + margin;
    const int max_width = dialog->dims.width - 2 * x;

    draw_util_text(message_intro, &(dialog->surface), white, black, x, y, max_width);
    y += config.font.height;

    draw_util_text(message_intro2, &(dialog->surface), white, black, x, y, max_width);
    y += config.font.height;

    char *bt_color = "#FFFFFF";
    if (backtrace_done < 0) {
        bt_color = "#AA0000";
    } else if (backtrace_done > 0) {
        bt_color = "#00AA00";
    }
    draw_util_text(message_option_backtrace, &(dialog->surface), draw_util_hex_to_color(bt_color), black, x, y, max_width);
    y += config.font.height;

    draw_util_text(message_option_restart, &(dialog->surface), white, black, x, y, max_width);
    y += config.font.height;

    draw_util_text(message_option_forget, &(dialog->surface), white, black, x, y, max_width);
    y += config.font.height;
}