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
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int cmp_idx_or_pack_name(const char *idx_or_pack_name,
				const char *idx_name)
{
	/* Skip past any initial matching prefix. */
	while (*idx_name && *idx_name == *idx_or_pack_name) {
		idx_name++;
		idx_or_pack_name++;
	}

	/*
	 * If we didn't match completely, we may have matched "pack-1234." and
	 * be left with "idx" and "pack" respectively, which is also OK. We do
	 * not have to check for "idx" and "idx", because that would have been
	 * a complete match (and in that case these strcmps will be false, but
	 * we'll correctly return 0 from the final strcmp() below.
	 *
	 * Technically this matches "fooidx" and "foopack", but we'd never have
	 * such names in the first place.
	 */
	if (!strcmp(idx_name, "idx") && !strcmp(idx_or_pack_name, "pack"))
		return 0;

	/*
	 * This not only checks for a complete match, but also orders based on
	 * the first non-identical character, which means our ordering will
	 * match a raw strcmp(). That makes it OK to use this to binary search
	 * a naively-sorted list.
	 */
	return strcmp(idx_or_pack_name, idx_name);
}