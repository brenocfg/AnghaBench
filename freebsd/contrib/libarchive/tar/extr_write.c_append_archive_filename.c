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
struct bsdtar {int return_value; int /*<<< orphan*/  bytes_per_block; int /*<<< orphan*/ * passphrase; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int append_archive (struct bsdtar*,struct archive*,struct archive*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int archive_read_add_passphrase (struct archive*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 scalar_t__ archive_read_open_filename (struct archive*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_set_options (struct archive*,char*) ; 
 int archive_read_set_passphrase_callback (struct archive*,struct bsdtar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  passphrase_callback ; 
 int /*<<< orphan*/  set_reader_options (struct bsdtar*,struct archive*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
append_archive_filename(struct bsdtar *bsdtar, struct archive *a,
    const char *raw_filename)
{
	struct archive *ina;
	const char *filename = raw_filename;
	int rc;

	if (strcmp(filename, "-") == 0)
		filename = NULL; /* Library uses NULL for stdio. */

	ina = archive_read_new();
	archive_read_support_format_all(ina);
	archive_read_support_filter_all(ina);
	set_reader_options(bsdtar, ina);
	archive_read_set_options(ina, "mtree:checkfs");
	if (bsdtar->passphrase != NULL)
		rc = archive_read_add_passphrase(a, bsdtar->passphrase);
	else
		rc = archive_read_set_passphrase_callback(ina, bsdtar,
			&passphrase_callback);
	if (rc != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(a));
	if (archive_read_open_filename(ina, filename,
					bsdtar->bytes_per_block)) {
		lafe_warnc(0, "%s", archive_error_string(ina));
		bsdtar->return_value = 1;
		return (0);
	}

	rc = append_archive(bsdtar, a, ina);

	if (rc != ARCHIVE_OK) {
		lafe_warnc(0, "Error reading archive %s: %s",
		    raw_filename, archive_error_string(ina));
		bsdtar->return_value = 1;
	}
	archive_read_free(ina);

	return (rc);
}