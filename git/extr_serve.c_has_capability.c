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
struct argv_array {int argc; int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 scalar_t__ skip_prefix (int /*<<< orphan*/ ,char const*,char const**) ; 

int has_capability(const struct argv_array *keys, const char *capability,
		   const char **value)
{
	int i;
	for (i = 0; i < keys->argc; i++) {
		const char *out;
		if (skip_prefix(keys->argv[i], capability, &out) &&
		    (!*out || *out == '=')) {
			if (value) {
				if (*out == '=')
					out++;
				*value = out;
			}
			return 1;
		}
	}

	return 0;
}