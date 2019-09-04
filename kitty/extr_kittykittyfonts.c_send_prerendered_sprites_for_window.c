#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sprite_map; int /*<<< orphan*/  cell_height; int /*<<< orphan*/  cell_width; } ;
struct TYPE_5__ {scalar_t__ fonts_data; } ;
typedef  TYPE_1__ OSWindow ;
typedef  TYPE_2__ FontGroup ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_sprite_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  send_prerendered_sprites (TYPE_2__*) ; 

void
send_prerendered_sprites_for_window(OSWindow *w) {
    FontGroup *fg = (FontGroup*)w->fonts_data;
    if (!fg->sprite_map) {
        fg->sprite_map = alloc_sprite_map(fg->cell_width, fg->cell_height);
        if (!fg->sprite_map) fatal("Out of memory allocating a sprite map");
        send_prerendered_sprites(fg);
    }
}