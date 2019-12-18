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
struct show_data {char const* pattern; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  REPLACE_FORMAT_LONG ; 
 int /*<<< orphan*/  REPLACE_FORMAT_MEDIUM ; 
 int /*<<< orphan*/  REPLACE_FORMAT_SHORT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  for_each_replace_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  show_reference ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int list_replace_refs(const char *pattern, const char *format)
{
	struct show_data data;

	if (pattern == NULL)
		pattern = "*";
	data.pattern = pattern;

	if (format == NULL || *format == '\0' || !strcmp(format, "short"))
		data.format = REPLACE_FORMAT_SHORT;
	else if (!strcmp(format, "medium"))
		data.format = REPLACE_FORMAT_MEDIUM;
	else if (!strcmp(format, "long"))
		data.format = REPLACE_FORMAT_LONG;
	/*
	 * Please update _git_replace() in git-completion.bash when
	 * you add new format
	 */
	else
		return error(_("invalid replace format '%s'\n"
			       "valid formats are 'short', 'medium' and 'long'"),
			     format);

	for_each_replace_ref(the_repository, show_reference, (void *)&data);

	return 0;
}