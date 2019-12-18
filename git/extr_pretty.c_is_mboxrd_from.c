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
 scalar_t__ starts_with (char const*,char*) ; 
 int strspn (char const*,char*) ; 

__attribute__((used)) static int is_mboxrd_from(const char *line, int len)
{
	/*
	 * a line matching /^From $/ here would only have len == 4
	 * at this point because is_empty_line would've trimmed all
	 * trailing space
	 */
	return len > 4 && starts_with(line + strspn(line, ">"), "From ");
}