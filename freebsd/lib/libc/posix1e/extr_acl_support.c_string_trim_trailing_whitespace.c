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

void
string_trim_trailing_whitespace(char *string)
{
	char	*end;

	if (*string == '\0')
		return;

	end = string + strlen(string) - 1;

	while (end != string) {
		if ((*end == ' ') || (*end == '\t')) {
			*end = '\0';
			end--;
		} else {
			return;
		}
	}

	return;
}