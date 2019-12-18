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
typedef  char Char ;

/* Variables and functions */

__attribute__((used)) static int
strtail(Char *cp, const char *str)
{
    while (*cp && *cp == (Char)*str)
	cp++, str++;
    return (*cp != '\0');
}