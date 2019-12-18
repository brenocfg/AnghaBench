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
struct archive_read_filter_bidder {char* name; int /*<<< orphan*/  free; int /*<<< orphan*/ * options; int /*<<< orphan*/  init; int /*<<< orphan*/  bid; int /*<<< orphan*/ * data; } ;
struct archive_read {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int ARCHIVE_WARN ; 
 scalar_t__ __archive_read_get_bidder (struct archive_read*,struct archive_read_filter_bidder**) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lrzip_bidder_bid ; 
 int /*<<< orphan*/  lrzip_bidder_init ; 
 int /*<<< orphan*/  lrzip_reader_free ; 

int
archive_read_support_filter_lrzip(struct archive *_a)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct archive_read_filter_bidder *reader;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_filter_lrzip");

	if (__archive_read_get_bidder(a, &reader) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	reader->data = NULL;
	reader->name = "lrzip";
	reader->bid = lrzip_bidder_bid;
	reader->init = lrzip_bidder_init;
	reader->options = NULL;
	reader->free = lrzip_reader_free;
	/* This filter always uses an external program. */
	archive_set_error(_a, ARCHIVE_ERRNO_MISC,
	    "Using external lrzip program for lrzip decompression");
	return (ARCHIVE_WARN);
}