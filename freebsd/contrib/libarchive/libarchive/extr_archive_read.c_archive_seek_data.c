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
struct archive_read {TYPE_1__* format; int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  la_int64_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* seek_data ) (struct archive_read*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_PROGRAMMER ; 
 int /*<<< orphan*/  ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_DATA ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct archive_read*,int /*<<< orphan*/ ,int) ; 

la_int64_t
archive_seek_data(struct archive *_a, int64_t offset, int whence)
{
	struct archive_read *a = (struct archive_read *)_a;
	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_DATA,
	    "archive_seek_data_block");

	if (a->format->seek_data == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "Internal error: "
		    "No format_seek_data_block function registered");
		return (ARCHIVE_FATAL);
	}

	return (a->format->seek_data)(a, offset, whence);
}