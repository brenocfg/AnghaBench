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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static u64 U8TOU64(const unsigned char *p)
{
    return (((u64)(p[0] & 0xff)) |
            ((u64)(p[1] & 0xff) << 8) |
            ((u64)(p[2] & 0xff) << 16) |
            ((u64)(p[3] & 0xff) << 24) |
            ((u64)(p[4] & 0xff) << 32) |
            ((u64)(p[5] & 0xff) << 40) |
            ((u64)(p[6] & 0xff) << 48) |
            ((u64)(p[7] & 0xff) << 56));
}