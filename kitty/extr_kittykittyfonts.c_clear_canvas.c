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
struct TYPE_3__ {int cell_width; int cell_height; scalar_t__ canvas; } ;
typedef  TYPE_1__ FontGroup ;

/* Variables and functions */
 int CELLS_IN_CANVAS ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
clear_canvas(FontGroup *fg) {
    if (fg->canvas) memset(fg->canvas, 0, CELLS_IN_CANVAS * fg->cell_width * fg->cell_height * sizeof(pixel));
}