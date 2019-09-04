#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int char_type ;
struct TYPE_10__ {TYPE_2__* glyph; } ;
struct TYPE_9__ {TYPE_6__* face; } ;
struct TYPE_7__ {scalar_t__ horiAdvance; } ;
struct TYPE_8__ {TYPE_1__ metrics; } ;
typedef  TYPE_3__ Face ;

/* Variables and functions */
 int FT_Get_Char_Index (TYPE_6__*,int) ; 
 int /*<<< orphan*/  FT_LOAD_DEFAULT ; 
 unsigned int MAX (unsigned int,unsigned int) ; 
 scalar_t__ ceilf (float) ; 
 scalar_t__ load_glyph (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int
calc_cell_width(Face *self) {
    unsigned int ans = 0;
    for (char_type i = 32; i < 128; i++) {
        int glyph_index = FT_Get_Char_Index(self->face, i);
        if (load_glyph(self, glyph_index, FT_LOAD_DEFAULT)) {
            ans = MAX(ans, (unsigned int)ceilf((float)self->face->glyph->metrics.horiAdvance / 64.f));
        }
    }
    return ans;
}