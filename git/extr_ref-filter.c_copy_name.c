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
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char const* xmemdupz (char const*,int) ; 
 char const* xstrdup (char*) ; 

__attribute__((used)) static const char *copy_name(const char *buf)
{
	const char *cp;
	for (cp = buf; *cp && *cp != '\n'; cp++) {
		if (!strncmp(cp, " <", 2))
			return xmemdupz(buf, cp - buf);
	}
	return xstrdup("");
}