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
typedef  scalar_t__ Char ;

/* Variables and functions */

int
any(const char *s, Char c)
{
    if (!s)
	return (0);		/* Check for nil pointer */
    while (*s)
	if ((Char)*s++ == c)
	    return (1);
    return (0);
}