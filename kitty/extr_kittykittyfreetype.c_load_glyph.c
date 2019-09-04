#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  face; int /*<<< orphan*/  hintstyle; int /*<<< orphan*/  hinting; } ;
typedef  TYPE_1__ Face ;

/* Variables and functions */
 int FT_Load_Glyph (int /*<<< orphan*/ ,int,int) ; 
 int get_load_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_freetype_error (char*,int) ; 

__attribute__((used)) static inline bool
load_glyph(Face *self, int glyph_index, int load_type) {
    int flags = get_load_flags(self->hinting, self->hintstyle, load_type);
    int error = FT_Load_Glyph(self->face, glyph_index, flags);
    if (error) { set_freetype_error("Failed to load glyph, with error:", error); return false; }
    return true;
}