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
typedef  int /*<<< orphan*/  glyph_index ;
struct TYPE_7__ {int /*<<< orphan*/  face; } ;
struct TYPE_6__ {int data; } ;
typedef  TYPE_1__ SpecialGlyphCache ;
typedef  TYPE_2__ Font ;

/* Variables and functions */
 int EMPTY_FILLED_MASK ; 
 int EMPTY_VALUE_MASK ; 
 scalar_t__ is_glyph_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* special_glyph_cache_for (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool
is_empty_glyph(glyph_index glyph_id, Font *font) {
    // A glyph is empty if its metrics have a width of zero
    SpecialGlyphCache *s = special_glyph_cache_for(font, glyph_id, EMPTY_FILLED_MASK);
    if (s == NULL) return false;
    if (!(s->data & EMPTY_FILLED_MASK)) {
        uint8_t val = is_glyph_empty(font->face, glyph_id) ? EMPTY_VALUE_MASK : 0;
        s->data |= val | EMPTY_FILLED_MASK;
    }
    return s->data & EMPTY_VALUE_MASK;
}