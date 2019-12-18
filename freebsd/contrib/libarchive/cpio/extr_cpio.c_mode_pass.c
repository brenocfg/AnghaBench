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
struct lafe_line_reader {int dummy; } ;
struct cpio {char* destdir; int /*<<< orphan*/  pass_destpath; int /*<<< orphan*/ * archive; int /*<<< orphan*/  quiet; scalar_t__ dot; int /*<<< orphan*/  linkresolver; int /*<<< orphan*/  option_null; int /*<<< orphan*/ * archive_read_disk; scalar_t__ option_follow_links; int /*<<< orphan*/  extract_flags; } ;
typedef  int int64_t ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_linkresolver_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_linkresolver_new () ; 
 int /*<<< orphan*/  archive_error_string (int /*<<< orphan*/ *) ; 
 int archive_filter_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * archive_read_disk_new () ; 
 int /*<<< orphan*/  archive_read_disk_set_standard_lookup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_disk_set_symlink_logical (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_read_disk_set_symlink_physical (int /*<<< orphan*/ *) ; 
 int archive_write_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * archive_write_disk_new () ; 
 int archive_write_disk_set_options (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_disk_set_standard_lookup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_write_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_to_archive (struct cpio*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,...) ; 
 struct lafe_line_reader* lafe_line_reader (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lafe_line_reader_free (struct lafe_line_reader*) ; 
 char* lafe_line_reader_next (struct lafe_line_reader*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
mode_pass(struct cpio *cpio, const char *destdir)
{
	struct lafe_line_reader *lr;
	const char *p;
	int r;
	size_t destdir_len;

	/* Ensure target dir has a trailing '/' to simplify path surgery. */
	destdir_len = strlen(destdir);
	cpio->destdir = malloc(destdir_len + 8);
	memcpy(cpio->destdir, destdir, destdir_len);
	if (destdir_len == 0 || destdir[destdir_len - 1] != '/')
		cpio->destdir[destdir_len++] = '/';
	cpio->destdir[destdir_len++] = '\0';

	cpio->archive = archive_write_disk_new();
	if (cpio->archive == NULL)
		lafe_errc(1, 0, "Failed to allocate archive object");
	r = archive_write_disk_set_options(cpio->archive, cpio->extract_flags);
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(cpio->archive));
	cpio->linkresolver = archive_entry_linkresolver_new();
	archive_write_disk_set_standard_lookup(cpio->archive);

	cpio->archive_read_disk = archive_read_disk_new();
	if (cpio->archive_read_disk == NULL)
		lafe_errc(1, 0, "Failed to allocate archive object");
	if (cpio->option_follow_links)
		archive_read_disk_set_symlink_logical(cpio->archive_read_disk);
	else
		archive_read_disk_set_symlink_physical(cpio->archive_read_disk);
	archive_read_disk_set_standard_lookup(cpio->archive_read_disk);

	lr = lafe_line_reader("-", cpio->option_null);
	while ((p = lafe_line_reader_next(lr)) != NULL)
		file_to_archive(cpio, p);
	lafe_line_reader_free(lr);

	archive_entry_linkresolver_free(cpio->linkresolver);
	r = archive_write_close(cpio->archive);
	if (cpio->dot)
		fprintf(stderr, "\n");
	if (r != ARCHIVE_OK)
		lafe_errc(1, 0, "%s", archive_error_string(cpio->archive));

	if (!cpio->quiet) {
		int64_t blocks =
			(archive_filter_bytes(cpio->archive, 0) + 511)
			/ 512;
		fprintf(stderr, "%lu %s\n", (unsigned long)blocks,
		    blocks == 1 ? "block" : "blocks");
	}

	archive_write_free(cpio->archive);
	free(cpio->pass_destpath);
}