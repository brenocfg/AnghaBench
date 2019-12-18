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
struct archive_write {char* format_name; int /*<<< orphan*/  format_finish_entry; int /*<<< orphan*/  (* format_free ) (struct archive_write*) ;int /*<<< orphan*/  format_close; int /*<<< orphan*/  format_write_data; int /*<<< orphan*/  format_write_header; struct ar_w* format_data; int /*<<< orphan*/  archive; } ;
struct ar_w {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_write_ar_close ; 
 int /*<<< orphan*/  archive_write_ar_data ; 
 int /*<<< orphan*/  archive_write_ar_finish_entry ; 
 int /*<<< orphan*/  archive_write_ar_free (struct archive_write*) ; 
 int /*<<< orphan*/  archive_write_ar_header ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  stub1 (struct archive_write*) ; 

__attribute__((used)) static int
archive_write_set_format_ar(struct archive_write *a)
{
	struct ar_w *ar;

	/* If someone else was already registered, unregister them. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	ar = (struct ar_w *)calloc(1, sizeof(*ar));
	if (ar == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Can't allocate ar data");
		return (ARCHIVE_FATAL);
	}
	a->format_data = ar;

	a->format_name = "ar";
	a->format_write_header = archive_write_ar_header;
	a->format_write_data = archive_write_ar_data;
	a->format_close = archive_write_ar_close;
	a->format_free = archive_write_ar_free;
	a->format_finish_entry = archive_write_ar_finish_entry;
	return (ARCHIVE_OK);
}