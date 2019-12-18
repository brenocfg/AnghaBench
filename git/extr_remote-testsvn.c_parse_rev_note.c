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
struct rev_note {long rev_nr; } ;

/* Variables and functions */
 long UINT32_MAX ; 
 scalar_t__ starts_with (char const*,char const*) ; 
 char* strchrnul (char const*,char) ; 
 int strlen (char const*) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_rev_note(const char *msg, struct rev_note *res)
{
	const char *key, *value, *end;
	size_t len;

	while (*msg) {
		end = strchrnul(msg, '\n');
		len = end - msg;

		key = "Revision-number: ";
		if (starts_with(msg, key)) {
			long i;
			char *end;
			value = msg + strlen(key);
			i = strtol(value, &end, 0);
			if (end == value || i < 0 || i > UINT32_MAX)
				return -1;
			res->rev_nr = i;
			return 0;
		}
		msg += len + 1;
	}
	/* didn't find it */
	return -1;
}