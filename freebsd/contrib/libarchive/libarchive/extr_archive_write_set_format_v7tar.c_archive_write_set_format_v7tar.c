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
typedef  int /*<<< orphan*/  template_header ;
struct v7tar {int dummy; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {char* format_name; TYPE_1__ archive; int /*<<< orphan*/  format_finish_entry; int /*<<< orphan*/  (* format_free ) (struct archive_write*) ;int /*<<< orphan*/  format_close; int /*<<< orphan*/  format_write_data; int /*<<< orphan*/  format_write_header; int /*<<< orphan*/  format_options; struct v7tar* format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_TAR ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  archive_write_v7tar_close ; 
 int /*<<< orphan*/  archive_write_v7tar_data ; 
 int /*<<< orphan*/  archive_write_v7tar_finish_entry ; 
 int /*<<< orphan*/  archive_write_v7tar_free (struct archive_write*) ; 
 int /*<<< orphan*/  archive_write_v7tar_header ; 
 int /*<<< orphan*/  archive_write_v7tar_options ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  stub1 (struct archive_write*) ; 

int
archive_write_set_format_v7tar(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct v7tar *v7tar;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_v7tar");

	/* If someone else was already registered, unregister them. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	/* Basic internal sanity test. */
	if (sizeof(template_header) != 512) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Internal: template_header wrong size: %zu should be 512",
		    sizeof(template_header));
		return (ARCHIVE_FATAL);
	}

	v7tar = (struct v7tar *)calloc(1, sizeof(*v7tar));
	if (v7tar == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate v7tar data");
		return (ARCHIVE_FATAL);
	}
	a->format_data = v7tar;
	a->format_name = "tar (non-POSIX)";
	a->format_options = archive_write_v7tar_options;
	a->format_write_header = archive_write_v7tar_header;
	a->format_write_data = archive_write_v7tar_data;
	a->format_close = archive_write_v7tar_close;
	a->format_free = archive_write_v7tar_free;
	a->format_finish_entry = archive_write_v7tar_finish_entry;
	a->archive.archive_format = ARCHIVE_FORMAT_TAR;
	a->archive.archive_format_name = "tar (non-POSIX)";
	return (ARCHIVE_OK);
}