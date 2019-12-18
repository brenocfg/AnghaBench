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
 scalar_t__ kmemmem (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

char *kstrstr(const char *str, const char *pat, int **_prep)
{
	return (char*)kmemmem(str, strlen(str), pat, strlen(pat), _prep);
}