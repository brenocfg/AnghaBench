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

/* Variables and functions */

__attribute__((used)) static void asn1_put_length(unsigned char **pp, int length)
{
    unsigned char *p = *pp;
    int i, l;
    if (length <= 127)
        *(p++) = (unsigned char)length;
    else {
        l = length;
        for (i = 0; l > 0; i++)
            l >>= 8;
        *(p++) = i | 0x80;
        l = i;
        while (i-- > 0) {
            p[i] = length & 0xff;
            length >>= 8;
        }
        p += l;
    }
    *pp = p;
}