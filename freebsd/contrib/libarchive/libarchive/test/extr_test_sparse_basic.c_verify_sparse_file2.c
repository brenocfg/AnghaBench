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
struct sparse {int dummy; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_set_pathname (struct archive_entry*,char const*) ; 
 int /*<<< orphan*/  archive_entry_sparse_count (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_disk_entry_from_file (struct archive*,struct archive_entry*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  failure (char const*) ; 
 int open (char const*,int) ; 

__attribute__((used)) static void
verify_sparse_file2(struct archive *a, const char *path,
    const struct sparse *sparse, int blocks, int preopen)
{
	struct archive_entry *ae;
	int fd;

	(void)sparse; /* UNUSED */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_pathname(ae, path);
	if (preopen)
		fd = open(path, O_RDONLY | O_BINARY);
	else
		fd = -1;
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_read_disk_entry_from_file(a, ae, fd, NULL));
	if (fd >= 0)
		close(fd);
	/* Verify the number of holes only, not its offset nor its
	 * length because those alignments are deeply dependence on
	 * its filesystem. */ 
	failure(path);
	assertEqualInt(blocks, archive_entry_sparse_count(ae));
	archive_entry_free(ae);
}