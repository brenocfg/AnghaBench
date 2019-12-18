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
 scalar_t__ is_dir_sep (char const) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static size_t
test_suffix(const char *suffix, const char *src_name, size_t src_len)
{
	const size_t suffix_len = strlen(suffix);

	// The filename must have at least one character in addition to
	// the suffix. src_name may contain path to the filename, so we
	// need to check for directory separator too.
	if (src_len <= suffix_len
			|| is_dir_sep(src_name[src_len - suffix_len - 1]))
		return 0;

	if (strcmp(suffix, src_name + src_len - suffix_len) == 0)
		return src_len - suffix_len;

	return 0;
}