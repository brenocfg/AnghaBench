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

__attribute__((used)) static unsigned int read_ledword(const unsigned char **in)
{
    const unsigned char *p = *in;
    unsigned int ret;
    ret = *p++;
    ret |= (*p++ << 8);
    ret |= (*p++ << 16);
    ret |= (*p++ << 24);
    *in = p;
    return ret;
}