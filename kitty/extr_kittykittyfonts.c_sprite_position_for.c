#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int glyph_index ;
struct TYPE_13__ {TYPE_2__* sprite_map; } ;
struct TYPE_10__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_12__ {TYPE_1__ sprite_tracker; } ;
struct TYPE_11__ {int glyph; int filled; scalar_t__ ligature_index; int rendered; int colored; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  extra_glyphs; struct TYPE_11__* next; } ;
typedef  TYPE_2__ SpritePosition ;
typedef  TYPE_3__ FontGroup ;
typedef  TYPE_4__ Font ;
typedef  int /*<<< orphan*/  ExtraGlyphs ;

/* Variables and functions */
 scalar_t__ LIKELY (int) ; 
 int SPECIAL_GLYPH_CACHE_SIZE ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  do_increment (TYPE_3__*,int*) ; 
 scalar_t__ extra_glyphs_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static SpritePosition*
sprite_position_for(FontGroup *fg, Font *font, glyph_index glyph, ExtraGlyphs *extra_glyphs, uint8_t ligature_index, int *error) {
    glyph_index idx = glyph & (SPECIAL_GLYPH_CACHE_SIZE - 1);
    SpritePosition *s = font->sprite_map + idx;
    // Optimize for the common case of glyph under 1024 already in the cache
    if (LIKELY(s->glyph == glyph && s->filled && extra_glyphs_equal(&s->extra_glyphs, extra_glyphs) && s->ligature_index == ligature_index)) return s;  // Cache hit
    while(true) {
        if (s->filled) {
            if (s->glyph == glyph && extra_glyphs_equal(&s->extra_glyphs, extra_glyphs) && s->ligature_index == ligature_index) return s;  // Cache hit
        } else {
            break;
        }
        if (!s->next) {
            s->next = calloc(1, sizeof(SpritePosition));
            if (s->next == NULL) { *error = 1; return NULL; }
        }
        s = s->next;
    }
    s->glyph = glyph;
    memcpy(&s->extra_glyphs, extra_glyphs, sizeof(ExtraGlyphs));
    s->ligature_index = ligature_index;
    s->filled = true;
    s->rendered = false;
    s->colored = false;
    s->x = fg->sprite_tracker.x; s->y = fg->sprite_tracker.y; s->z = fg->sprite_tracker.z;
    do_increment(fg, error);
    return s;
}