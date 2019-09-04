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
typedef  int uint8_t ;
typedef  int pixel ;
struct TYPE_4__ {size_t top; size_t bottom; size_t left; size_t right; } ;
typedef  TYPE_1__ Region ;

/* Variables and functions */

__attribute__((used)) static inline void
copy_color_bitmap(uint8_t *src, pixel* dest, Region *src_rect, Region *dest_rect, size_t src_stride, size_t dest_stride) {
    for (size_t sr = src_rect->top, dr = dest_rect->top; sr < src_rect->bottom && dr < dest_rect->bottom; sr++, dr++) {
        pixel *d = dest + dest_stride * dr;
        uint8_t *s = src + src_stride * sr;
        for(size_t sc = src_rect->left, dc = dest_rect->left; sc < src_rect->right && dc < dest_rect->right; sc++, dc++) {
            uint8_t *bgra = s + 4 * sc;
            if (bgra[3]) {
#define C(idx, shift) ( (uint8_t)(((float)bgra[idx] / (float)bgra[3]) * 255) << shift)
                d[dc] = C(2, 24) | C(1, 16) | C(0, 8) | bgra[3];
#undef C
        } else d[dc] = 0;
        }
    }
}