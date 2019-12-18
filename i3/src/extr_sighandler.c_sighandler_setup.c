#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int height; } ;
struct TYPE_4__ {TYPE_1__ font; } ;

/* Variables and functions */
 int border_width ; 
 TYPE_2__ config ; 
 int dialog_height ; 
 int dialog_width ; 
 void* i3string_from_utf8 (char*) ; 
 int logical_px (int) ; 
 int margin ; 
 void* message_intro ; 
 void* message_intro2 ; 
 void* message_option_backtrace ; 
 void* message_option_forget ; 
 void* message_option_restart ; 
 int predict_text_width (void*) ; 

__attribute__((used)) static void sighandler_setup(void) {
    border_width = logical_px(border_width);
    margin = logical_px(margin);

    int num_lines = 5;
    message_intro = i3string_from_utf8("i3 has just crashed. Please report a bug for this.");
    message_intro2 = i3string_from_utf8("To debug this problem, you can either attach gdb or choose from the following options:");
    message_option_backtrace = i3string_from_utf8("- 'b' to save a backtrace (requires gdb)");
    message_option_restart = i3string_from_utf8("- 'r' to restart i3 in-place");
    message_option_forget = i3string_from_utf8("- 'f' to forget the previous layout and restart i3");

    int width_longest_message = predict_text_width(message_intro2);

    dialog_width = width_longest_message + 2 * border_width + 2 * margin;
    dialog_height = num_lines * config.font.height + 2 * border_width + 2 * margin;
}