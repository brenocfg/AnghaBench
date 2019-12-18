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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static int
unicode_to_utf8(char *p, uint32_t uc)
{        
        char *_p = p;

        /* Translate code point to UTF8 */
        if (uc <= 0x7f) {
                *p++ = (char)uc;
        } else if (uc <= 0x7ff) {
                *p++ = 0xc0 | ((uc >> 6) & 0x1f);
                *p++ = 0x80 | (uc & 0x3f);
        } else if (uc <= 0xffff) {
                *p++ = 0xe0 | ((uc >> 12) & 0x0f);
                *p++ = 0x80 | ((uc >> 6) & 0x3f);
                *p++ = 0x80 | (uc & 0x3f);
        } else {
                *p++ = 0xf0 | ((uc >> 18) & 0x07);
                *p++ = 0x80 | ((uc >> 12) & 0x3f);
                *p++ = 0x80 | ((uc >> 6) & 0x3f);
                *p++ = 0x80 | (uc & 0x3f);
        }
        return ((int)(p - _p));
}