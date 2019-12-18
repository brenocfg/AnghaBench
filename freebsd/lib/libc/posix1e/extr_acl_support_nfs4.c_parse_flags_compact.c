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
typedef  int /*<<< orphan*/  uint32_t ;
struct flagnames_struct {char const letter; int /*<<< orphan*/  flag; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  warnx (char*,char const*,char const) ; 

__attribute__((used)) static int
parse_flags_compact(const char *str, uint32_t *var,
    const struct flagnames_struct *flags, const char *flags_name)
{
	int i, j, found;

	*var = 0;

	for (i = 0;; i++) {
		if (str[i] == '\0')
			return (0);

		/* Ignore minus signs. */
		if (str[i] == '-')
			continue;

		found = 0;

		for (j = 0; flags[j].name != NULL; j++) {
			if (flags[j].letter == str[i]) {
				*var |= flags[j].flag;
				found = 1;
				break;
			}
		}

		if (!found) {
			warnx("malformed ACL: \"%s\" field contains "
			    "invalid flag \"%c\"", flags_name, str[i]);
			return (-1);
		}
	}
}