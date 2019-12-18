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
 scalar_t__ ISDIGIT (char const) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
version_number(const char *base, const char *backup, size_t base_length)
{
	int		version;
	const char	*p;

	version = 0;
	if (!strncmp(base, backup, base_length) && ISDIGIT(backup[base_length])) {
		for (p = &backup[base_length]; ISDIGIT(*p); ++p)
			version = version * 10 + *p - '0';
		if (p[0] != '~' || p[1])
			version = 0;
	}
	return version;
}