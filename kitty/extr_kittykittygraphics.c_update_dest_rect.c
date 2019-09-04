#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int width; int height; } ;
struct TYPE_5__ {int src_width; int cell_x_offset; int src_height; int cell_y_offset; int effective_num_rows; int effective_num_cols; } ;
typedef  TYPE_1__ ImageRef ;
typedef  TYPE_2__ CellPixelSize ;

/* Variables and functions */

__attribute__((used)) static inline void
update_dest_rect(ImageRef *ref, uint32_t num_cols, uint32_t num_rows, CellPixelSize cell) {
    uint32_t t;
    if (num_cols == 0) {
        t = ref->src_width + ref->cell_x_offset;
        num_cols = t / cell.width;
        if (t > num_cols * cell.width) num_cols += 1;
    }
    if (num_rows == 0) {
        t = ref->src_height + ref->cell_y_offset;
        num_rows = t / cell.height;
        if (t > num_rows * cell.height) num_rows += 1;
    }
    ref->effective_num_rows = num_rows;
    ref->effective_num_cols = num_cols;
}