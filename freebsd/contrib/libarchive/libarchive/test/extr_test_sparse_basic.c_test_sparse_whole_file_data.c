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
struct archive_entry {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_sparse_add_entry (struct archive_entry*,scalar_t__,int) ; 
 int /*<<< orphan*/  archive_entry_sparse_count (struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void
test_sparse_whole_file_data()
{
	struct archive_entry *ae;
	int64_t offset;
	int i;

	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_size(ae, 1024*10);

	/*
	 * Add sparse block data up to the file size.
	 */
	offset = 0;
	for (i = 0; i < 10; i++) {
		archive_entry_sparse_add_entry(ae, offset, 1024);
		offset += 1024;
	}

	failure("There should be no sparse");
	assertEqualInt(0, archive_entry_sparse_count(ae));
	archive_entry_free(ae);
}