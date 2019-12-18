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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static unsigned char
negative(signed char b)
{
    /* 18446744073709551361..18446744073709551615: yes; 0..255: no */
    uint64_t x = b;

    x >>= 63; /* 1: yes; 0: no */

    return x;
}