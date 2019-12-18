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
typedef  unsigned char uint32_t ;

/* Variables and functions */

__attribute__((used)) static void
decode_le_uint32(const void *ptr, uint32_t *n)
{
    const unsigned char *p = ptr;
    *n = (p[0] << 0) | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}