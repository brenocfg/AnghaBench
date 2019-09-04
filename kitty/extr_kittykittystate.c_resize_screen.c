#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* fonts_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_11__ {TYPE_1__ cell_size; } ;
struct TYPE_10__ {int /*<<< orphan*/  cell_height; int /*<<< orphan*/  cell_width; } ;
typedef  TYPE_3__ Screen ;
typedef  TYPE_4__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  screen_dirty_sprite_positions (TYPE_3__*) ; 
 int /*<<< orphan*/  screen_rescale_images (TYPE_3__*) ; 

__attribute__((used)) static inline void
resize_screen(OSWindow *os_window, Screen *screen, bool has_graphics) {
    if (screen) {
        screen->cell_size.width = os_window->fonts_data->cell_width;
        screen->cell_size.height = os_window->fonts_data->cell_height;
        screen_dirty_sprite_positions(screen);
        if (has_graphics) screen_rescale_images(screen);
    }
}