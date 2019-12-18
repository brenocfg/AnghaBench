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
 int strlen (char*) ; 

__attribute__((used)) static int parse_ext_names(char *names, const char **result)
{
    char *p, *q;
    int cnt = 0, len = 0;

    p = q = names;
    len = strlen(names);

    while (q - names <= len) {
        if (*q != ',' && *q != '\0') {
            q++;
            continue;
        }
        if (p != q) {
            /* found */
            if (result != NULL) {
                result[cnt] = p;
                *q = '\0';
            }
            cnt++;
        }
        p = ++q;
    }

    return cnt;
}