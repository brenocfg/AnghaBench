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
struct shar {int /*<<< orphan*/  quoted_name; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {char* format_name; TYPE_1__ archive; int /*<<< orphan*/  format_finish_entry; int /*<<< orphan*/  format_write_data; int /*<<< orphan*/  (* format_free ) (struct archive_write*) ;int /*<<< orphan*/  format_close; int /*<<< orphan*/  format_write_header; struct shar* format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_SHAR_BASE ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_string_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_write_shar_close ; 
 int /*<<< orphan*/  archive_write_shar_data_sed ; 
 int /*<<< orphan*/  archive_write_shar_finish_entry ; 
 int /*<<< orphan*/  archive_write_shar_free (struct archive_write*) ; 
 int /*<<< orphan*/  archive_write_shar_header ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  stub1 (struct archive_write*) ; 

int
archive_write_set_format_shar(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct shar *shar;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_shar");

	/* If someone else was already registered, unregister them. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	shar = (struct shar *)calloc(1, sizeof(*shar));
	if (shar == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Can't allocate shar data");
		return (ARCHIVE_FATAL);
	}
	archive_string_init(&shar->work);
	archive_string_init(&shar->quoted_name);
	a->format_data = shar;
	a->format_name = "shar";
	a->format_write_header = archive_write_shar_header;
	a->format_close = archive_write_shar_close;
	a->format_free = archive_write_shar_free;
	a->format_write_data = archive_write_shar_data_sed;
	a->format_finish_entry = archive_write_shar_finish_entry;
	a->archive.archive_format = ARCHIVE_FORMAT_SHAR_BASE;
	a->archive.archive_format_name = "shar";
	return (ARCHIVE_OK);
}