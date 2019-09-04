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
typedef  int ssize_t ;
struct TYPE_3__ {int width; size_t rows; int* buf; size_t stride; size_t start_x; } ;
typedef  TYPE_1__ ProcessedBitmap ;

/* Variables and functions */

__attribute__((used)) static inline void
trim_borders(ProcessedBitmap *ans, size_t extra) {
    bool column_has_text = false;

    // Trim empty columns from the right side of the bitmap
    for (ssize_t x = ans->width - 1; !column_has_text && x > -1 && extra > 0; x--) {
        for (size_t y = 0; y < ans->rows && !column_has_text; y++) {
            if (ans->buf[x + y * ans->stride] > 200) column_has_text = true;
        }
        if (!column_has_text) { ans->width--; extra--; }
    }

    // Remove any remaining extra columns from the left edge of the bitmap
    ans->start_x = extra;
    ans->width -= extra;
}