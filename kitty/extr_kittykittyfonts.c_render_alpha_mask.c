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
typedef  scalar_t__ uint8_t ;
typedef  int pixel ;
struct TYPE_4__ {size_t top; size_t bottom; size_t left; size_t right; } ;
typedef  TYPE_1__ Region ;

/* Variables and functions */
 int MIN (int,scalar_t__) ; 

void
render_alpha_mask(uint8_t *alpha_mask, pixel* dest, Region *src_rect, Region *dest_rect, size_t src_stride, size_t dest_stride) {
    for (size_t sr = src_rect->top, dr = dest_rect->top; sr < src_rect->bottom && dr < dest_rect->bottom; sr++, dr++) {
        pixel *d = dest + dest_stride * dr;
        uint8_t *s = alpha_mask + src_stride * sr;
        for(size_t sc = src_rect->left, dc = dest_rect->left; sc < src_rect->right && dc < dest_rect->right; sc++, dc++) {
            pixel val = d[dc];
            uint8_t alpha = s[sc];
            d[dc] = 0xffffff00 | MIN(0xff, alpha + (val & 0xff));
        }
    }
}