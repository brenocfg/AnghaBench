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
 scalar_t__ isalnum (int) ; 
 int /*<<< orphan*/  isascii (int) ; 
 int /*<<< orphan*/  msg (char*,char const*) ; 

__attribute__((used)) static int
okname(const char *cp0)
{
	const char *cp;
	int c;

	for (cp = cp0; *cp; cp++) {
		c = *cp;
		if (!isascii(c) || !(isalnum(c) || c == '_' || c == '-')) {
			msg("invalid user name %s\n", cp0);
			return (0);
		}
	}
	return (1);
}