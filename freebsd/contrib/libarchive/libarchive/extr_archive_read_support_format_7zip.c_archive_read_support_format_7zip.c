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
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;
struct _7zip {int /*<<< orphan*/  has_encrypted_entries; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ENOMEM ; 
 int __archive_read_register_format (struct archive_read*,struct _7zip*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_read_format_7zip_bid ; 
 int /*<<< orphan*/  archive_read_format_7zip_cleanup ; 
 int /*<<< orphan*/  archive_read_format_7zip_has_encrypted_entries ; 
 int /*<<< orphan*/  archive_read_format_7zip_read_data ; 
 int /*<<< orphan*/  archive_read_format_7zip_read_data_skip ; 
 int /*<<< orphan*/  archive_read_format_7zip_read_header ; 
 int /*<<< orphan*/  archive_read_support_format_7zip_capabilities ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct _7zip* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct _7zip*) ; 

int
archive_read_support_format_7zip(struct archive *_a)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct _7zip *zip;
	int r;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_read_support_format_7zip");

	zip = calloc(1, sizeof(*zip));
	if (zip == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate 7zip data");
		return (ARCHIVE_FATAL);
	}

	/*
	 * Until enough data has been read, we cannot tell about
	 * any encrypted entries yet.
	 */
	zip->has_encrypted_entries = ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW;


	r = __archive_read_register_format(a,
	    zip,
	    "7zip",
	    archive_read_format_7zip_bid,
	    NULL,
	    archive_read_format_7zip_read_header,
	    archive_read_format_7zip_read_data,
	    archive_read_format_7zip_read_data_skip,
	    NULL,
	    archive_read_format_7zip_cleanup,
	    archive_read_support_format_7zip_capabilities,
	    archive_read_format_7zip_has_encrypted_entries);

	if (r != ARCHIVE_OK)
		free(zip);
	return (ARCHIVE_OK);
}