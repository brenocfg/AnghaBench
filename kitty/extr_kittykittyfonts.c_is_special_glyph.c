#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ glyph_index ;
struct TYPE_10__ {scalar_t__ current_codepoint; } ;
struct TYPE_9__ {int /*<<< orphan*/  face; } ;
struct TYPE_8__ {int data; } ;
typedef  TYPE_1__ SpecialGlyphCache ;
typedef  TYPE_2__ Font ;
typedef  TYPE_3__ CellData ;

/* Variables and functions */
 int SPECIAL_FILLED_MASK ; 
 int SPECIAL_VALUE_MASK ; 
 scalar_t__ glyph_id_for_codepoint (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* special_glyph_cache_for (TYPE_2__*,scalar_t__,int) ; 

__attribute__((used)) static inline bool
is_special_glyph(glyph_index glyph_id, Font *font, CellData* cell_data) {
    // A glyph is special if the codepoint it corresponds to matches a
    // different glyph in the font
    SpecialGlyphCache *s = special_glyph_cache_for(font, glyph_id, SPECIAL_FILLED_MASK);
    if (s == NULL) return false;
    if (!(s->data & SPECIAL_FILLED_MASK)) {
        bool is_special = cell_data->current_codepoint ? (
            glyph_id != glyph_id_for_codepoint(font->face, cell_data->current_codepoint) ? true : false)
            :
            false;
        uint8_t val = is_special ? SPECIAL_VALUE_MASK : 0;
        s->data |= val | SPECIAL_FILLED_MASK;
    }
    return s->data & SPECIAL_VALUE_MASK;
}