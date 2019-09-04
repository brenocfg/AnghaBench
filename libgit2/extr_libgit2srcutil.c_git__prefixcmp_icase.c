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
 int /*<<< orphan*/  SIZE_MAX ; 
 int prefixcmp (char const*,int /*<<< orphan*/ ,char const*,int) ; 

int git__prefixcmp_icase(const char *str, const char *prefix)
{
	return prefixcmp(str, SIZE_MAX, prefix, true);
}