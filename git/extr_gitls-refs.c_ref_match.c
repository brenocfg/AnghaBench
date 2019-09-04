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
struct argv_array {int argc; char** argv; } ;

/* Variables and functions */
 scalar_t__ starts_with (char const*,char const*) ; 

__attribute__((used)) static int ref_match(const struct argv_array *prefixes, const char *refname)
{
	int i;

	if (!prefixes->argc)
		return 1; /* no restriction */

	for (i = 0; i < prefixes->argc; i++) {
		const char *prefix = prefixes->argv[i];

		if (starts_with(refname, prefix))
			return 1;
	}

	return 0;
}