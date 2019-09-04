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

__attribute__((used)) static int contains_crlf_only(const char *s, size_t len)
{
    for (; len != 0; ++s, --len)
        if (!(*s == '\r' || *s == '\n'))
            return 0;
    return 1;
}