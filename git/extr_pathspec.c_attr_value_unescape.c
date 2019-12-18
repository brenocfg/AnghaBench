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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ invalid_value_char (char const) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* xmallocz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *attr_value_unescape(const char *value)
{
	const char *src;
	char *dst, *ret;

	ret = xmallocz(strlen(value));
	for (src = value, dst = ret; *src; src++, dst++) {
		if (*src == '\\') {
			if (!src[1])
				die(_("Escape character '\\' not allowed as "
				      "last character in attr value"));
			src++;
		}
		if (invalid_value_char(*src))
			die("cannot use '%c' for value matching", *src);
		*dst = *src;
	}
	*dst = '\0';
	return ret;
}