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
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git__isdigit (char const) ; 
 scalar_t__ git__strntol32 (int*,char const*,int /*<<< orphan*/ ,char const**,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int extract_how_many(int *n, const char *spec, size_t *pos)
{
	const char *end_ptr;
	int parsed, accumulated;
	char kind = spec[*pos];

	assert(spec[*pos] == '^' || spec[*pos] == '~');

	accumulated = 0;

	do {
		do {
			(*pos)++;
			accumulated++;
		} while (spec[(*pos)] == kind && kind == '~');

		if (git__isdigit(spec[*pos])) {
			if (git__strntol32(&parsed, spec + *pos, strlen(spec + *pos), &end_ptr, 10) < 0)
				return GIT_EINVALIDSPEC;

			accumulated += (parsed - 1);
			*pos = end_ptr - spec;
		}

	} 	while (spec[(*pos)] == kind && kind == '~');

	*n = accumulated;

	return 0;
}