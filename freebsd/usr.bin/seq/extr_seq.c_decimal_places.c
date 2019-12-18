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
 int /*<<< orphan*/  decimal_point ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 char* strstr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
decimal_places(const char *number)
{
	int places = 0;
	char *dp;

	/* look for a decimal point */
	if ((dp = strstr(number, decimal_point))) {
		dp += strlen(decimal_point);

		while (isdigit((unsigned char)*dp++))
			places++;
	}
	return (places);
}