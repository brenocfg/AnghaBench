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
 int /*<<< orphan*/  isalnum (char const) ; 
 scalar_t__ toupper (char const) ; 

__attribute__((used)) static size_t match_string(const char *date, const char *str)
{
	size_t i = 0;

	for (i = 0; *date; date++, str++, i++) {
		if (*date == *str)
			continue;
		if (toupper(*date) == toupper(*str))
			continue;
		if (!isalnum(*date))
			break;
		return 0;
	}
	return i;
}