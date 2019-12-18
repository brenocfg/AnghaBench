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
struct gnutar {int dummy; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {char* format_name; TYPE_1__ archive; int /*<<< orphan*/  format_finish_entry; int /*<<< orphan*/  format_free; int /*<<< orphan*/  format_close; int /*<<< orphan*/  format_write_data; int /*<<< orphan*/  format_write_header; int /*<<< orphan*/  format_options; struct gnutar* format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_TAR_GNUTAR ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_write_gnutar_close ; 
 int /*<<< orphan*/  archive_write_gnutar_data ; 
 int /*<<< orphan*/  archive_write_gnutar_finish_entry ; 
 int /*<<< orphan*/  archive_write_gnutar_free ; 
 int /*<<< orphan*/  archive_write_gnutar_header ; 
 int /*<<< orphan*/  archive_write_gnutar_options ; 
 scalar_t__ calloc (int,int) ; 

int
archive_write_set_format_gnutar(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct gnutar *gnutar;

	gnutar = (struct gnutar *)calloc(1, sizeof(*gnutar));
	if (gnutar == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate gnutar data");
		return (ARCHIVE_FATAL);
	}
	a->format_data = gnutar;
	a->format_name = "gnutar";
	a->format_options = archive_write_gnutar_options;
	a->format_write_header = archive_write_gnutar_header;
	a->format_write_data = archive_write_gnutar_data;
	a->format_close = archive_write_gnutar_close;
	a->format_free = archive_write_gnutar_free;
	a->format_finish_entry = archive_write_gnutar_finish_entry;
	a->archive.archive_format = ARCHIVE_FORMAT_TAR_GNUTAR;
	a->archive.archive_format_name = "GNU tar";
	return (ARCHIVE_OK);
}