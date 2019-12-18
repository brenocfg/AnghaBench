#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_read_filter_bidder {int (* bid ) (struct archive_read_filter_bidder*,struct archive_read_filter*) ;int (* init ) (struct archive_read_filter*) ;} ;
struct archive_read_filter {struct archive_read_filter* upstream; struct archive_read* archive; struct archive_read_filter_bidder* bidder; int /*<<< orphan*/  code; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  compression_code; int /*<<< orphan*/  compression_name; } ;
struct archive_read {TYPE_1__ archive; struct archive_read_filter* filter; struct archive_read_filter_bidder* bidders; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int MAX_NUMBER_FILTERS ; 
 int /*<<< orphan*/  __archive_read_filter_ahead (struct archive_read_filter*,int,scalar_t__*) ; 
 int /*<<< orphan*/  __archive_read_free_filters (struct archive_read*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (int,int) ; 
 int stub1 (struct archive_read_filter_bidder*,struct archive_read_filter*) ; 
 int stub2 (struct archive_read_filter*) ; 

__attribute__((used)) static int
choose_filters(struct archive_read *a)
{
	int number_bidders, i, bid, best_bid, number_filters;
	struct archive_read_filter_bidder *bidder, *best_bidder;
	struct archive_read_filter *filter;
	ssize_t avail;
	int r;

	for (number_filters = 0; number_filters < MAX_NUMBER_FILTERS; ++number_filters) {
		number_bidders = sizeof(a->bidders) / sizeof(a->bidders[0]);

		best_bid = 0;
		best_bidder = NULL;

		bidder = a->bidders;
		for (i = 0; i < number_bidders; i++, bidder++) {
			if (bidder->bid != NULL) {
				bid = (bidder->bid)(bidder, a->filter);
				if (bid > best_bid) {
					best_bid = bid;
					best_bidder = bidder;
				}
			}
		}

		/* If no bidder, we're done. */
		if (best_bidder == NULL) {
			/* Verify the filter by asking it for some data. */
			__archive_read_filter_ahead(a->filter, 1, &avail);
			if (avail < 0) {
				__archive_read_free_filters(a);
				return (ARCHIVE_FATAL);
			}
			a->archive.compression_name = a->filter->name;
			a->archive.compression_code = a->filter->code;
			return (ARCHIVE_OK);
		}

		filter
		    = (struct archive_read_filter *)calloc(1, sizeof(*filter));
		if (filter == NULL)
			return (ARCHIVE_FATAL);
		filter->bidder = best_bidder;
		filter->archive = a;
		filter->upstream = a->filter;
		a->filter = filter;
		r = (best_bidder->init)(a->filter);
		if (r != ARCHIVE_OK) {
			__archive_read_free_filters(a);
			return (ARCHIVE_FATAL);
		}
	}
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Input requires too many filters for decoding");
	return (ARCHIVE_FATAL);
}