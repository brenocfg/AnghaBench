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

__attribute__((used)) static void write_ledword(unsigned char **out, unsigned int dw)
{
    unsigned char *p = *out;
    *p++ = dw & 0xff;
    *p++ = (dw >> 8) & 0xff;
    *p++ = (dw >> 16) & 0xff;
    *p++ = (dw >> 24) & 0xff;
    *out = p;
}