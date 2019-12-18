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

__attribute__((used)) static void encode_uint16(void *_p, unsigned v)
{
    unsigned char *p = _p;
    p[0] = (unsigned char)(v >> 8);
    p[1] = (unsigned char)v;
}