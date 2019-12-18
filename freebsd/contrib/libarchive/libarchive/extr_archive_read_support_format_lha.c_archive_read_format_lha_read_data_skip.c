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
struct lha {int end_of_entry_cleanup; int end_of_entry; scalar_t__ entry_bytes_remaining; scalar_t__ entry_unconsumed; } ;
struct archive_read {TYPE_1__* format; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ __archive_read_consume (struct archive_read*,scalar_t__) ; 

__attribute__((used)) static int
archive_read_format_lha_read_data_skip(struct archive_read *a)
{
	struct lha *lha;
	int64_t bytes_skipped;

	lha = (struct lha *)(a->format->data);

	if (lha->entry_unconsumed) {
		/* Consume as much as the decompressor actually used. */
		__archive_read_consume(a, lha->entry_unconsumed);
		lha->entry_unconsumed = 0;
	}

	/* if we've already read to end of data, we're done. */
	if (lha->end_of_entry_cleanup)
		return (ARCHIVE_OK);

	/*
	 * If the length is at the beginning, we can skip the
	 * compressed data much more quickly.
	 */
	bytes_skipped = __archive_read_consume(a, lha->entry_bytes_remaining);
	if (bytes_skipped < 0)
		return (ARCHIVE_FATAL);

	/* This entry is finished and done. */
	lha->end_of_entry_cleanup = lha->end_of_entry = 1;
	return (ARCHIVE_OK);
}