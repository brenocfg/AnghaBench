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
typedef  unsigned int uint8_t ;
struct TYPE_3__ {unsigned int width; unsigned int rows; unsigned int* buf; unsigned int stride; int needs_free; int factor; } ;
typedef  TYPE_1__ ProcessedBitmap ;

/* Variables and functions */
 float MAX (float,float) ; 
 unsigned int MIN (unsigned int,unsigned int) ; 
 unsigned int* calloc (int,unsigned int) ; 
 int ceilf (float) ; 
 int /*<<< orphan*/  fatal (char*) ; 

__attribute__((used)) static void
downsample_bitmap(ProcessedBitmap *bm, unsigned int width, unsigned int cell_height) {
    // Downsample using a simple area averaging algorithm. Could probably do
    // better with bi-cubic or lanczos, but at these small sizes I don't think
    // it matters
    float ratio = MAX((float)bm->width / width, (float)bm->rows / cell_height);
    int factor = ceilf(ratio);
    uint8_t *dest = calloc(4, width * cell_height);
    if (dest == NULL) fatal("Out of memory");
    uint8_t *d = dest;

    for (unsigned int i = 0, sr = 0; i < cell_height; i++, sr += factor) {
        for (unsigned int j = 0, sc = 0; j < width; j++, sc += factor, d += 4) {

            // calculate area average
            unsigned int r=0, g=0, b=0, a=0, count=0;
            for (unsigned int y=sr; y < MIN(sr + factor, bm->rows); y++) {
                uint8_t *p = bm->buf + (y * bm->stride) + sc * 4;
                for (unsigned int x=sc; x < MIN(sc + factor, bm->width); x++, count++) {
                    b += *(p++); g += *(p++); r += *(p++); a += *(p++);
                }
            }
            if (count) {
                d[0] = b / count; d[1] = g / count; d[2] = r / count; d[3] = a / count;
            }

        }
    }
    bm->buf = dest; bm->needs_free = true; bm->stride = 4 * width; bm->width = width; bm->rows = cell_height;
    bm->factor = factor;
}