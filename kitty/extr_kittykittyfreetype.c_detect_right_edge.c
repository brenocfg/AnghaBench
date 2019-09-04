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
typedef  int uint8_t ;
typedef  int ssize_t ;
struct TYPE_3__ {int right_edge; int width; size_t rows; int* buf; size_t stride; } ;
typedef  TYPE_1__ ProcessedBitmap ;

/* Variables and functions */

__attribute__((used)) static inline void
detect_right_edge(ProcessedBitmap *ans) {
    ans->right_edge = 0;
    for (ssize_t x = ans->width - 1; !ans->right_edge && x > -1; x--) {
        for (size_t y = 0; y < ans->rows && !ans->right_edge; y++) {
            uint8_t *p = ans->buf + x * 4 + y * ans->stride;
            if (p[3] > 20) ans->right_edge = x;
        }
    }
}