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
typedef  int uint64_t ;
struct bsdtar {scalar_t__ verbose; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int archive_entry_size (struct archive_entry*) ; 
 int archive_file_count (struct archive*) ; 
 int archive_filter_bytes (struct archive*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  safe_fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* tar_i64toa (int) ; 

__attribute__((used)) static void
report_write(struct bsdtar *bsdtar, struct archive *a,
    struct archive_entry *entry, int64_t progress)
{
	uint64_t comp, uncomp;
	int compression;

	if (bsdtar->verbose)
		fprintf(stderr, "\n");
	comp = archive_filter_bytes(a, -1);
	uncomp = archive_filter_bytes(a, 0);
	fprintf(stderr, "In: %d files, %s bytes;",
	    archive_file_count(a), tar_i64toa(uncomp));
	if (comp >= uncomp)
		compression = 0;
	else
		compression = (int)((uncomp - comp) * 100 / uncomp);
	fprintf(stderr,
	    " Out: %s bytes, compression %d%%\n",
	    tar_i64toa(comp), compression);
	/* Can't have two calls to tar_i64toa() pending, so split the output. */
	safe_fprintf(stderr, "Current: %s (%s",
	    archive_entry_pathname(entry),
	    tar_i64toa(progress));
	fprintf(stderr, "/%s bytes)\n",
	    tar_i64toa(archive_entry_size(entry)));
}