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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t ntoh64(const uint8_t *src)
{
    return (uint64_t)src[0] << 56 | (uint64_t)src[1] << 48 | (uint64_t)src[2] << 40 | (uint64_t)src[3] << 32 |
           (uint64_t)src[4] << 24 | (uint64_t)src[5] << 16 | (uint64_t)src[6] << 8 | src[7];
}