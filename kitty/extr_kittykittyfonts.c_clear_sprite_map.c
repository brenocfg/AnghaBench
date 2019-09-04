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
struct TYPE_5__ {TYPE_1__* sprite_map; } ;
struct TYPE_4__ {int filled; int rendered; int colored; scalar_t__ ligature_index; scalar_t__ z; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  extra_glyphs; scalar_t__ glyph; struct TYPE_4__* next; } ;
typedef  TYPE_1__ SpritePosition ;
typedef  TYPE_2__ Font ;
typedef  int /*<<< orphan*/  ExtraGlyphs ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
clear_sprite_map(Font *font) {
#define CLEAR(s) s->filled = false; s->rendered = false; s->colored = false; s->glyph = 0; memset(&s->extra_glyphs, 0, sizeof(ExtraGlyphs)); s->x = 0; s->y = 0; s->z = 0; s->ligature_index = 0;
    SpritePosition *s;
    for (size_t i = 0; i < sizeof(font->sprite_map)/sizeof(font->sprite_map[0]); i++) {
        s = font->sprite_map + i;
        CLEAR(s);
        while ((s = s->next)) {
            CLEAR(s);
        }
    }
#undef CLEAR
}