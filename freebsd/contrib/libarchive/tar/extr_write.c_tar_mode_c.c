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
struct bsdtar {int /*<<< orphan*/  filename; int /*<<< orphan*/ * passphrase; int /*<<< orphan*/  cset; int /*<<< orphan*/  bytes_in_last_block; int /*<<< orphan*/  bytes_per_block; int /*<<< orphan*/ * names_from_file; int /*<<< orphan*/ ** argv; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 char const* archive_error_string (struct archive*) ; 
 struct archive* archive_write_new () ; 
 int archive_write_open_filename (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_set_bytes_in_last_block (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_set_bytes_per_block (struct archive*,int /*<<< orphan*/ ) ; 
 int archive_write_set_format_by_name (struct archive*,char*) ; 
 int archive_write_set_format_pax_restricted (struct archive*) ; 
 int archive_write_set_passphrase (struct archive*,int /*<<< orphan*/ *) ; 
 int archive_write_set_passphrase_callback (struct archive*,struct bsdtar*,int /*<<< orphan*/ *) ; 
 char* cset_get_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cset_set_format (int /*<<< orphan*/ ,char*) ; 
 int cset_write_add_filters (int /*<<< orphan*/ ,struct archive*,void const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  passphrase_callback ; 
 int /*<<< orphan*/  set_writer_options (struct bsdtar*,struct archive*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  write_archive (struct archive*,struct bsdtar*) ; 

void
tar_mode_c(struct bsdtar *bsdtar)
{
	struct archive *a;
	const void *filter_name;
	int r;

	if (*bsdtar->argv == NULL && bsdtar->names_from_file == NULL)
		lafe_errc(1, 0, "no files or directories specified");

	a = archive_write_new();

	/* Support any format that the library supports. */
	if (cset_get_format(bsdtar->cset) == NULL) {
		r = archive_write_set_format_pax_restricted(a);
		cset_set_format(bsdtar->cset, "pax restricted");
	} else {
		r = archive_write_set_format_by_name(a,
			cset_get_format(bsdtar->cset));
	}
	if (r != ARCHIVE_OK) {
		fprintf(stderr, "Can't use format %s: %s\n",
		    cset_get_format(bsdtar->cset),
		    archive_error_string(a));
		usage();
	}

	archive_write_set_bytes_per_block(a, bsdtar->bytes_per_block);
	archive_write_set_bytes_in_last_block(a, bsdtar->bytes_in_last_block);

	r = cset_write_add_filters(bsdtar->cset, a, &filter_name);
	if (r < ARCHIVE_WARN) {
		lafe_errc(1, 0, "Unsupported compression option --%s",
		    (const char *)filter_name);
	}

	set_writer_options(bsdtar, a);
	if (bsdtar->passphrase != NULL)
		r = archive_write_set_passphrase(a, bsdtar->passphrase);
	else
		r = archive_write_set_passphrase_callback(a, bsdtar,
			&passphrase_callback);
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(a));
	if (ARCHIVE_OK != archive_write_open_filename(a, bsdtar->filename))
		lafe_errc(1, 0, "%s", archive_error_string(a));
	write_archive(a, bsdtar);
}