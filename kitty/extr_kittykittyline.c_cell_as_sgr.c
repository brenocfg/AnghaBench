#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int attrs; int /*<<< orphan*/  decoration_fg; int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; } ;
typedef  TYPE_1__ GPUCell ;

/* Variables and functions */
 int BOLD_SHIFT ; 
 int DECORATION_FG_CODE ; 
 int DECORATION_MASK ; 
 int DECORATION_SHIFT ; 
 int DIM_SHIFT ; 
 int ITALIC_SHIFT ; 
 int REVERSE_SHIFT ; 
 int STRIKE_SHIFT ; 
 int /*<<< orphan*/  color_as_sgr (char*,int,int /*<<< orphan*/ ,int,int,int) ; 
 char* decoration_as_sgr (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 

const char*
cell_as_sgr(GPUCell *cell, GPUCell *prev) {
    static char buf[128];
#define SZ sizeof(buf) - (p - buf) - 2
#define P(s) { size_t len = strlen(s); if (SZ > len) { memcpy(p, s, len); p += len; } }
    char *p = buf;
#define CMP(attr) (attr(cell) != attr(prev))
#define BOLD(cell) (cell->attrs & (1 << BOLD_SHIFT))
#define DIM(cell) (cell->attrs & (1 << DIM_SHIFT))
#define ITALIC(cell) (cell->attrs & (1 << ITALIC_SHIFT))
#define REVERSE(cell) (cell->attrs & (1 << REVERSE_SHIFT))
#define STRIKETHROUGH(cell) (cell->attrs & (1 << STRIKE_SHIFT))
#define DECORATION(cell) (cell->attrs & (DECORATION_MASK << DECORATION_SHIFT))
    bool intensity_differs = CMP(BOLD) || CMP(DIM);
    if (intensity_differs) {
        if (!BOLD(cell) && !DIM(cell)) { P("22;"); }
        else { if (BOLD(cell)) P("1;"); if (DIM(cell)) P("2;"); }
    }
    if (CMP(ITALIC)) P(ITALIC(cell) ? "3;" : "23;");
    if (CMP(REVERSE)) P(REVERSE(cell) ? "7;" : "27;");
    if (CMP(STRIKETHROUGH)) P(STRIKETHROUGH(cell) ? "9;" : "29;");
    if (cell->fg != prev->fg) p += color_as_sgr(p, SZ, cell->fg, 30, 90, 38);
    if (cell->bg != prev->bg) p += color_as_sgr(p, SZ, cell->bg, 40, 100, 48);
    if (cell->decoration_fg != prev->decoration_fg) p += color_as_sgr(p, SZ, cell->decoration_fg, 0, 0, DECORATION_FG_CODE);
    if (CMP(DECORATION)) P(decoration_as_sgr((cell->attrs >> DECORATION_SHIFT) & DECORATION_MASK));
#undef CMP
#undef BOLD
#undef DIM
#undef ITALIC
#undef REVERSE
#undef STRIKETHROUGH
#undef DECORATION
#undef P
#undef SZ
    if (p > buf) *(p - 1) = 0;  // remove trailing semi-colon
    *p = 0;  // ensure string is null-terminated
    return buf;
}