#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* next; } ;
struct TYPE_8__ {TYPE_4__* special_glyph_cache; TYPE_4__* sprite_map; } ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_1__ SpritePosition ;
typedef  TYPE_1__ SpecialGlyphCache ;
typedef  TYPE_3__ Font ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

void
free_maps(Font *font) {
#define free_a_map(type, attr) {\
    type *s, *t; \
    for (size_t i = 0; i < sizeof(font->attr)/sizeof(font->attr[0]); i++) { \
        s = font->attr[i].next; \
        while (s) { \
            t = s; \
            s = s->next; \
            free(t); \
        } \
    }\
    memset(font->attr, 0, sizeof(font->attr)); \
}
    free_a_map(SpritePosition, sprite_map);
    free_a_map(SpecialGlyphCache, special_glyph_cache);
#undef free_a_map
}