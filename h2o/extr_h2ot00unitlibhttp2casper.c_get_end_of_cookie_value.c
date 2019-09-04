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

__attribute__((used)) static size_t get_end_of_cookie_value(char *cookie, size_t cookie_len)
{
    size_t i;
    for (i = 0; i != cookie_len; ++i)
        if (cookie[i] == ';')
            break;
    return i;
}