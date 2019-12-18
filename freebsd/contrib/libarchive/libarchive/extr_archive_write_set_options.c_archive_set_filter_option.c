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
struct archive_write_filter {int (* options ) (struct archive_write_filter*,char const*,char const*) ;int /*<<< orphan*/  name; struct archive_write_filter* next_filter; } ;
struct archive_write {struct archive_write_filter* filter_first; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int stub1 (struct archive_write_filter*,char const*,char const*) ; 

__attribute__((used)) static int
archive_set_filter_option(struct archive *_a, const char *m, const char *o,
    const char *v)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct archive_write_filter *filter;
	int r, rv = ARCHIVE_WARN;

	for (filter = a->filter_first; filter != NULL; filter = filter->next_filter) {
		if (filter->options == NULL)
			continue;
		if (m != NULL && strcmp(filter->name, m) != 0)
			continue;

		r = filter->options(filter, o, v);

		if (r == ARCHIVE_FATAL)
			return (ARCHIVE_FATAL);

		if (m != NULL)
			return (r);

		if (r == ARCHIVE_OK)
			rv = ARCHIVE_OK;
	}
	/* If the filter name didn't match, return a special code for
	 * _archive_set_option[s]. */
	if (rv == ARCHIVE_WARN && m != NULL)
		rv = ARCHIVE_WARN - 1;
	return (rv);
}