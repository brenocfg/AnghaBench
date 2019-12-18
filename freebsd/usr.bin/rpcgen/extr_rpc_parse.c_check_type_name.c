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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ ** reserved_types ; 
 int /*<<< orphan*/ ** reserved_words ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
check_type_name(const char *name, int new_type)
{
	int i;
	char tmp[100];

	for (i = 0; reserved_words[i] != NULL; i++) {
		if (strcmp(name, reserved_words[i]) == 0) {
			sprintf(tmp,
				"illegal (reserved) name :\'%s\' in type definition",
				name);
			error(tmp);
		}
	}
	if (new_type) {
		for (i = 0; reserved_types[i] != NULL; i++) {
			if (strcmp(name, reserved_types[i]) == 0) {
				sprintf(tmp,
					"illegal (reserved) name :\'%s\' in type definition",
					name);
				error(tmp);
			}
		}
	}
}