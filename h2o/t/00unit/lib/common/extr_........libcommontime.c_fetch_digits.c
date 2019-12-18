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

__attribute__((used)) static int fetch_digits(const char *s, size_t n)
{
    int value = 0;
    for (; n != 0; ++s, --n) {
        if (!('0' <= *s && *s <= '9'))
            return -1;
        value = value * 10 + *s - '0';
    }
    return value;
}