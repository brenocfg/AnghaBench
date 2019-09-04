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
 scalar_t__ tolower (char const) ; 

int istarts_with(const char *str, const char *prefix)
{
	for (; ; str++, prefix++)
		if (!*prefix)
			return 1;
		else if (tolower(*str) != tolower(*prefix))
			return 0;
}