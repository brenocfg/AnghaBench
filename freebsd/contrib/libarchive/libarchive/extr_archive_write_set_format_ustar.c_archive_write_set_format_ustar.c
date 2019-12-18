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
struct ustar {int dummy; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {char* format_name; TYPE_1__ archive; int /*<<< orphan*/  format_finish_entry; int /*<<< orphan*/  (* format_free ) (struct archive_write*) ;int /*<<< orphan*/  format_close; int /*<<< orphan*/  format_write_data; int /*<<< orphan*/  format_write_header; int /*<<< orphan*/  format_options; struct ustar* format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_TAR_USTAR ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  archive_write_ustar_close ; 
 int /*<<< orphan*/  archive_write_ustar_data ; 
 int /*<<< orphan*/  archive_write_ustar_finish_entry ; 
 int /*<<< orphan*/  archive_write_ustar_free (struct archive_write*) ; 
 int /*<<< orphan*/  archive_write_ustar_header ; 
 int /*<<< orphan*/  archive_write_ustar_options ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  stub1 (struct archive_write*) ; 

int
archive_write_set_format_ustar(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct ustar *ustar;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_ustar");

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

	ustar = (struct ustar *)calloc(1, sizeof(*ustar));
	if (ustar == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate ustar data");
		return (ARCHIVE_FATAL);
	}
	a->format_data = ustar;
	a->format_name = "ustar";
	a->format_options = archive_write_ustar_options;
	a->format_write_header = archive_write_ustar_header;
	a->format_write_data = archive_write_ustar_data;
	a->format_close = archive_write_ustar_close;
	a->format_free = archive_write_ustar_free;
	a->format_finish_entry = archive_write_ustar_finish_entry;
	a->archive.archive_format = ARCHIVE_FORMAT_TAR_USTAR;
	a->archive.archive_format_name = "POSIX ustar";
	return (ARCHIVE_OK);
}