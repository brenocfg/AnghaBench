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

__attribute__((used)) static const char* __itt_fsplit(const char* s, const char* sep, const char** out, int* len)
{
    int i;
    int j;

    if (!s || !sep || !out || !len)
        return NULL;

    for (i = 0; s[i]; i++)
    {
        int b = 0;
        for (j = 0; sep[j]; j++)
            if (s[i] == sep[j])
            {
                b = 1;
                break;
            }
        if (!b)
            break;
    }

    if (!s[i])
        return NULL;

    *len = 0;
    *out = &s[i];

    for (; s[i]; i++, (*len)++)
    {
        int b = 0;
        for (j = 0; sep[j]; j++)
            if (s[i] == sep[j])
            {
                b = 1;
                break;
            }
        if (b)
            break;
    }

    for (; s[i]; i++)
    {
        int b = 0;
        for (j = 0; sep[j]; j++)
            if (s[i] == sep[j])
            {
                b = 1;
                break;
            }
        if (!b)
            break;
    }

    return &s[i];
}