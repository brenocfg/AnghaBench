#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  archive_format; } ;
struct archive_read {TYPE_1__ archive; TYPE_2__* format; } ;
struct archive_entry {int dummy; } ;
struct ar {int read_global_header; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_AR ; 
 void* __archive_read_ahead (struct archive_read*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,size_t) ; 
 int _ar_read_header (struct archive_read*,struct archive_entry*,struct ar*,char const*,size_t*) ; 

__attribute__((used)) static int
archive_read_format_ar_read_header(struct archive_read *a,
    struct archive_entry *entry)
{
	struct ar *ar = (struct ar*)(a->format->data);
	size_t unconsumed;
	const void *header_data;
	int ret;

	if (!ar->read_global_header) {
		/*
		 * We are now at the beginning of the archive,
		 * so we need first consume the ar global header.
		 */
		__archive_read_consume(a, 8);
		ar->read_global_header = 1;
		/* Set a default format code for now. */
		a->archive.archive_format = ARCHIVE_FORMAT_AR;
	}

	/* Read the header for the next file entry. */
	if ((header_data = __archive_read_ahead(a, 60, NULL)) == NULL)
		/* Broken header. */
		return (ARCHIVE_EOF);
	
	unconsumed = 60;
	
	ret = _ar_read_header(a, entry, ar, (const char *)header_data, &unconsumed);

	if (unconsumed)
		__archive_read_consume(a, unconsumed);

	return ret;
}