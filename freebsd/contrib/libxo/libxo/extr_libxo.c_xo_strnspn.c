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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/ * strchr (char const*,char const) ; 

__attribute__((used)) static ssize_t
xo_strnspn (const char *str, size_t len,  const char *accept)
{
    ssize_t i;
    const char *cp, *ep;

    for (i = 0, cp = str, ep = str + len; cp < ep && *cp != '\0'; i++, cp++) {
	if (strchr(accept, *cp) == NULL)
	    break;
    }

    return i;
}