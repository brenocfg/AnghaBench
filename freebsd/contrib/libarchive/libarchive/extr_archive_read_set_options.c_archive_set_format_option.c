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
struct archive_read {struct archive_format_descriptor* format; struct archive_format_descriptor* formats; } ;
struct archive_format_descriptor {int (* options ) (struct archive_read*,char const*,char const*) ;int /*<<< orphan*/ * name; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int stub1 (struct archive_read*,char const*,char const*) ; 

__attribute__((used)) static int
archive_set_format_option(struct archive *_a, const char *m, const char *o,
    const char *v)
{
	struct archive_read *a = (struct archive_read *)_a;
	size_t i;
	int r, rv = ARCHIVE_WARN, matched_modules = 0;

	for (i = 0; i < sizeof(a->formats)/sizeof(a->formats[0]); i++) {
		struct archive_format_descriptor *format = &a->formats[i];

		if (format->options == NULL || format->name == NULL)
			/* This format does not support option. */
			continue;
		if (m != NULL) {
			if (strcmp(format->name, m) != 0)
				continue;
			++matched_modules;
		}

		a->format = format;
		r = format->options(a, o, v);
		a->format = NULL;

		if (r == ARCHIVE_FATAL)
			return (ARCHIVE_FATAL);

		if (r == ARCHIVE_OK)
			rv = ARCHIVE_OK;
	}
	/* If the format name didn't match, return a special code for
	 * _archive_set_option[s]. */
	if (m != NULL && matched_modules == 0)
		return ARCHIVE_WARN - 1;
	return (rv);
}