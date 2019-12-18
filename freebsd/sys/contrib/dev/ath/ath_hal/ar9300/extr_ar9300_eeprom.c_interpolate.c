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
typedef  int u_int16_t ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static int
interpolate(int32_t x, int32_t *px, int32_t *py, u_int16_t np)
{
    int ip = 0;
    int lx = 0, ly = 0, lhave = 0;
    int hx = 0, hy = 0, hhave = 0;
    int dx = 0;
    int y = 0;
    int bf, factor, plus;

    lhave = 0;
    hhave = 0;
    /*
     * identify best lower and higher x calibration measurement
     */
    for (ip = 0; ip < np; ip++) {
        dx = x - px[ip];
        /* this measurement is higher than our desired x */
        if (dx <= 0) {
            if (!hhave || dx > (x - hx)) {
                /* new best higher x measurement */
                hx = px[ip];
                hy = py[ip];
                hhave = 1;
            }
        }
        /* this measurement is lower than our desired x */
        if (dx >= 0) {
            if (!lhave || dx < (x - lx)) {
                /* new best lower x measurement */
                lx = px[ip];
                ly = py[ip];
                lhave = 1;
            }
        }
    }
    /* the low x is good */
    if (lhave) {
        /* so is the high x */
        if (hhave) {
            /* they're the same, so just pick one */
            if (hx == lx) {
                y = ly;
            } else {
                /* interpolate with round off */
                bf = (2 * (hy - ly) * (x - lx)) / (hx - lx);
                plus = (bf % 2);
                factor = bf / 2;
                y = ly + factor + plus;
            }
        } else {
            /* only low is good, use it */
            y = ly;
        }
    } else if (hhave) {
        /* only high is good, use it */
        y = hy;
    } else {
        /* nothing is good,this should never happen unless np=0, ????  */
        y = -(1 << 30);
    }

    return y;
}