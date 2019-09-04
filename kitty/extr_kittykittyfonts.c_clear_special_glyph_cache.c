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
struct TYPE_5__ {TYPE_1__* special_glyph_cache; } ;
struct TYPE_4__ {scalar_t__ glyph; scalar_t__ data; struct TYPE_4__* next; } ;
typedef  TYPE_1__ SpecialGlyphCache ;
typedef  TYPE_2__ Font ;

/* Variables and functions */

void
clear_special_glyph_cache(Font *font) {
#define CLEAR(s) s->data = 0; s->glyph = 0;
    SpecialGlyphCache *s;
    for (size_t i = 0; i < sizeof(font->special_glyph_cache)/sizeof(font->special_glyph_cache[0]); i++) {
        s = font->special_glyph_cache + i;
        CLEAR(s);
        while ((s = s->next)) {
            CLEAR(s);
        }
    }
#undef CLEAR
}