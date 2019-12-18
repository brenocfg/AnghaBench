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
 int /*<<< orphan*/  custom_suffix ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ has_dir_sep (char const*) ; 
 int /*<<< orphan*/  message_fatal (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

extern void
suffix_set(const char *suffix)
{
	// Empty suffix and suffixes having a directory separator are
	// rejected. Such suffixes would break things later.
	if (suffix[0] == '\0' || has_dir_sep(suffix))
		message_fatal(_("%s: Invalid filename suffix"), suffix);

	// Replace the old custom_suffix (if any) with the new suffix.
	free(custom_suffix);
	custom_suffix = xstrdup(suffix);
	return;
}