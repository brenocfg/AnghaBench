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
 scalar_t__ OPENPAM_FEATURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESTRICT_MODULE_NAME ; 
 int /*<<< orphan*/  is_pfcs (char const) ; 

__attribute__((used)) static int
valid_module_name(const char *name)
{
	const char *p;

	if (OPENPAM_FEATURE(RESTRICT_MODULE_NAME)) {
		/* path separator not allowed */
		for (p = name; *p != '\0'; ++p)
			if (!is_pfcs(*p))
				return (0);
	} else {
		/* path separator allowed */
		for (p = name; *p != '\0'; ++p)
			if (!is_pfcs(*p) && *p != '/')
				return (0);
	}
	return (1);
}