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
typedef  int /*<<< orphan*/  pixel ;
struct TYPE_3__ {int cell_width; int cell_height; int /*<<< orphan*/ * canvas; } ;
typedef  TYPE_1__ FontGroup ;

/* Variables and functions */
 int CELLS_IN_CANVAS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline pixel*
extract_cell_from_canvas(FontGroup *fg, unsigned int i, unsigned int num_cells) {
    pixel *ans = fg->canvas + (fg->cell_width * fg->cell_height * (CELLS_IN_CANVAS - 1)), *dest = ans, *src = fg->canvas + (i * fg->cell_width);
    unsigned int stride = fg->cell_width * num_cells;
    for (unsigned int r = 0; r < fg->cell_height; r++, dest += fg->cell_width, src += stride) memcpy(dest, src, fg->cell_width * sizeof(pixel));
    return ans;
}