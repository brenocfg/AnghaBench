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
 int utf8_strnwidth (char const*,int,int /*<<< orphan*/ ) ; 

int utf8_strwidth(const char *string)
{
	return utf8_strnwidth(string, -1, 0);
}