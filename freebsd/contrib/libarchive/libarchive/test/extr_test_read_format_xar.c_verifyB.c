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
struct archive {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 scalar_t__ archive_read_data (struct archive*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 scalar_t__ archive_read_next_header (struct archive*,struct archive_entry**) ; 
 scalar_t__ archive_read_open_memory (struct archive*,unsigned char*,size_t) ; 
 scalar_t__ archive_read_support_filter_bzip2 (struct archive*) ; 
 scalar_t__ archive_read_support_filter_gzip (struct archive*) ; 
 scalar_t__ archive_read_support_format_xar (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  skipping (char*) ; 

__attribute__((used)) static void verifyB(unsigned char *d, size_t s) {
	struct archive* a;
	struct archive_entry *entry = NULL;
	size_t buf_size;
	unsigned char *buf;

	assert((a = archive_read_new()) != NULL);

	if(ARCHIVE_OK != archive_read_support_filter_gzip(a)) {
		skipping("Unsupported gzip");
		assertEqualInt(ARCHIVE_OK, archive_read_free(a));
		return;
	}

	if(ARCHIVE_OK != archive_read_support_filter_bzip2(a)) {
		skipping("Unsupported bzip2");
		assertEqualInt(ARCHIVE_OK, archive_read_free(a));
		return;
	}

	if(ARCHIVE_OK != archive_read_support_format_xar(a)) {
		skipping("Unsupported xar");
		assertEqualInt(ARCHIVE_OK, archive_read_free(a));
		return;
	}

	assertA(0 == archive_read_open_memory(a, d, s));

	// f1, content "onetwothree\n", size 12 bytes
	assertA(0 == archive_read_next_header(a, &entry));
	buf_size = (size_t) archive_entry_size(entry);
	assertA(buf_size == 12);
	buf = (unsigned char*) malloc(buf_size);
	assertA(NULL != buf);
	assertA(buf_size == (size_t) archive_read_data(a, buf, buf_size));
	free(buf);

	// f2, content "fourfivesix\n", size 12 bytes
	assertA(0 == archive_read_next_header(a, &entry));
	buf_size = (size_t) archive_entry_size(entry);
	assertA(buf_size == 12);
	buf = (unsigned char*) malloc(buf_size);
	assertA(NULL != buf);
	assertA(buf_size == (size_t) archive_read_data(a, buf, buf_size));
	free(buf);

	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}