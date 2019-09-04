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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline void
parse_color(unsigned int *params, unsigned int *i, unsigned int count, uint32_t *result) {
    unsigned int attr;
    uint8_t r, g, b;
    if (*i < count) {
        attr = params[(*i)++];
        switch(attr) {
            case 5:
                if (*i < count) *result = (params[(*i)++] & 0xFF) << 8 | 1;
                break;
            case 2: \
                if (*i < count - 2) {
                    /* Ignore the first parameter in a four parameter RGB */
                    /* sequence (unused color space id), see https://github.com/kovidgoyal/kitty/issues/227 */
                    if (*i < count - 3) (*i)++;
                    r = params[(*i)++] & 0xFF;
                    g = params[(*i)++] & 0xFF;
                    b = params[(*i)++] & 0xFF;
                    *result = r << 24 | g << 16 | b << 8 | 2;
                }
                break;
        }
    }
}