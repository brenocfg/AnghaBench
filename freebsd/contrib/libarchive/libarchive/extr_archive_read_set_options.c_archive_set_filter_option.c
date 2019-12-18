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
struct archive_read_filter_bidder {int (* options ) (struct archive_read_filter_bidder*,char const*,char const*) ;} ;
struct archive_read_filter {int /*<<< orphan*/  name; struct archive_read_filter_bidder* bidder; struct archive_read_filter* upstream; } ;
struct archive_read {struct archive_read_filter* filter; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int stub1 (struct archive_read_filter_bidder*,char const*,char const*) ; 

__attribute__((used)) static int
archive_set_filter_option(struct archive *_a, const char *m, const char *o,
    const char *v)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct archive_read_filter *filter;
	struct archive_read_filter_bidder *bidder;
	int r, rv = ARCHIVE_WARN, matched_modules = 0;

	for (filter = a->filter; filter != NULL; filter = filter->upstream) {
		bidder = filter->bidder;
		if (bidder == NULL)
			continue;
		if (bidder->options == NULL)
			/* This bidder does not support option */
			continue;
		if (m != NULL) {
			if (strcmp(filter->name, m) != 0)
				continue;
			++matched_modules;
		}

		r = bidder->options(bidder, o, v);

		if (r == ARCHIVE_FATAL)
			return (ARCHIVE_FATAL);

		if (r == ARCHIVE_OK)
			rv = ARCHIVE_OK;
	}
	/* If the filter name didn't match, return a special code for
	 * _archive_set_option[s]. */
	if (m != NULL && matched_modules == 0)
		return ARCHIVE_WARN - 1;
	return (rv);
}