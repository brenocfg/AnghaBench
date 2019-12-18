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
 scalar_t__ ERANGE ; 
 unsigned long long ULLONG_MAX ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 unsigned long long strtoull (char const*,char**,int) ; 

__attribute__((used)) static unsigned long long
get_bytes(const char *str)
{
	unsigned long long bytes;
	char *cp;

	bytes = strtoull(str, &cp, 10);
	if (bytes == ULLONG_MAX && errno == ERANGE)
		err(1, "%s", str);

	if (cp[0] != '\0') {
		if (cp[1] != '\0')
			errx(1, "invalid byte count: %s", str);
		if (cp[0] == 'k' || cp[0] == 'K')
			bytes *= 1024;
		else if (cp[0] == 'm' || cp[0] == 'M')
			bytes *= 1024 * 1024;
		else if (cp[0] == 'g' || cp[0] == 'G')
			bytes *= 1024 * 1024 * 1024;
		else
			errx(1, "invalid byte count modifier: %s", str);
	}

	return (bytes);
}