#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pixel ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
right_shift_canvas(pixel *canvas, size_t width, size_t height, size_t amt) {
    pixel *src;
    size_t r;
    for (r = 0, src = canvas; r < height; r++, src += width) {
        memmove(src + amt, src, sizeof(pixel) * (width - amt));
        memset(src, 0, sizeof(pixel) * amt);
    }
}