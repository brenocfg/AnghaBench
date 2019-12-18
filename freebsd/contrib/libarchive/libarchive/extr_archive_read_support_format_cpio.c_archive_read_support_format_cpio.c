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
struct cpio {int /*<<< orphan*/  magic; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  CPIO_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int __archive_read_register_format (struct archive_read*,struct cpio*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_read_format_cpio_bid ; 
 int /*<<< orphan*/  archive_read_format_cpio_cleanup ; 
 int /*<<< orphan*/  archive_read_format_cpio_options ; 
 int /*<<< orphan*/  archive_read_format_cpio_read_data ; 
 int /*<<< orphan*/  archive_read_format_cpio_read_header ; 
 int /*<<< orphan*/  archive_read_format_cpio_skip ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct cpio*) ; 

int
archive_read_support_format_cpio(struct archive *_a)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct cpio *cpio;
	int r;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_cpio");

	cpio = (struct cpio *)calloc(1, sizeof(*cpio));
	if (cpio == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Can't allocate cpio data");
		return (ARCHIVE_FATAL);
	}
	cpio->magic = CPIO_MAGIC;

	r = __archive_read_register_format(a,
	    cpio,
	    "cpio",
	    archive_read_format_cpio_bid,
	    archive_read_format_cpio_options,
	    archive_read_format_cpio_read_header,
	    archive_read_format_cpio_read_data,
	    archive_read_format_cpio_skip,
	    NULL,
	    archive_read_format_cpio_cleanup,
	    NULL,
	    NULL);

	if (r != ARCHIVE_OK)
		free(cpio);
	return (ARCHIVE_OK);
}