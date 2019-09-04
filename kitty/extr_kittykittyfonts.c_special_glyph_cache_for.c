#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int glyph_index ;
struct TYPE_7__ {TYPE_1__* special_glyph_cache; } ;
struct TYPE_6__ {int glyph; int data; struct TYPE_6__* next; } ;
typedef  TYPE_1__ SpecialGlyphCache ;
typedef  TYPE_2__ Font ;

/* Variables and functions */
 scalar_t__ LIKELY (int) ; 
 TYPE_1__* calloc (int,int) ; 

__attribute__((used)) static inline SpecialGlyphCache*
special_glyph_cache_for(Font *font, glyph_index glyph, uint8_t filled_mask) {
    SpecialGlyphCache *s = font->special_glyph_cache + (glyph & 0x3ff);
    // Optimize for the common case of glyph under SPECIAL_GLYPH_CACHE_SIZE already in the cache
    if (LIKELY(s->glyph == glyph && s->data & filled_mask)) return s;  // Cache hit
    while(true) {
        if (s->data & filled_mask) {
            if (s->glyph == glyph) return s;  // Cache hit
        } else {
            if (!s->glyph) break;  // Empty cache slot
            else if (s->glyph == glyph) return s;  // Cache slot that contains other data than the data indicated by filled_mask
        }
        if (!s->next) {
            s->next = calloc(1, sizeof(SpecialGlyphCache));
            if (s->next == NULL) return NULL;
        }
        s = s->next;
    }
    s->glyph = glyph;
    return s;
}