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
struct contents {scalar_t__ s; int o; char* d; } ;
struct archive_entry {int dummy; } ;
struct archive_contents {int /*<<< orphan*/ * filename; struct contents* contents; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ; 
 int archive_entry_is_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int archive_read_close (struct archive*) ; 
 int archive_read_data_block (struct archive*,void const**,scalar_t__*,int*) ; 
 char archive_read_free (struct archive*) ; 
 int archive_read_has_encrypted_entries (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 scalar_t__ archive_read_open_filename (struct archive*,char const*,int) ; 
 scalar_t__ archive_read_support_filter_all (struct archive*) ; 
 scalar_t__ archive_read_support_format_tar (struct archive*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,char) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_reference_file (char const*) ; 
 int /*<<< orphan*/  failure (char*,char const*,...) ; 

__attribute__((used)) static void
verify_archive_file(const char *name, struct archive_contents *ac)
{
	struct archive_entry *ae;
	int err;
	/* data, size, offset of next expected block. */
	struct contents expect;
	/* data, size, offset of block read from archive. */
	struct contents actual;
	const void *p;
	struct archive *a;

	extract_reference_file(name);

	assert((a = archive_read_new()) != NULL);
	assert(0 == archive_read_support_filter_all(a));
	assert(0 == archive_read_support_format_tar(a));
	failure("Can't open %s", name);
	assert(0 == archive_read_open_filename(a, name, 3));

	while (ac->filename != NULL) {
		struct contents *cts = ac->contents;

		if (!assertEqualIntA(a, 0, archive_read_next_header(a, &ae))) {
			assertEqualInt(ARCHIVE_OK, archive_read_free(a));
			return;
		}
		failure("Name mismatch in archive %s", name);
		assertEqualString(ac->filename, archive_entry_pathname(ae));
		assertEqualInt(archive_entry_is_encrypted(ae), 0);
		assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);

		expect = *cts++;
		while (0 == (err = archive_read_data_block(a,
				 &p, &actual.s, &actual.o))) {
			actual.d = p;
			while (actual.s > 0) {
				char c = *actual.d;
				if(actual.o < expect.o) {
					/*
					 * Any byte before the expected
					 * data must be NULL.
					 */
					failure("%s: pad at offset %d "
					    "should be zero", name, actual.o);
					assertEqualInt(c, 0);
				} else if (actual.o == expect.o) {
					/*
					 * Data at matching offsets must match.
					 */
					assertEqualInt(c, *expect.d);
					expect.d++;
					expect.o++;
					expect.s--;
					/* End of expected? step to next expected. */
					if (expect.s <= 0)
						expect = *cts++;
				} else {
					/*
					 * We found data beyond that expected.
					 */
					failure("%s: Unexpected trailing data",
					    name);
					assert(actual.o <= expect.o);
					archive_read_free(a);
					return;
				}
				actual.d++;
				actual.o++;
				actual.s--;
			}
		}
		failure("%s: should be end of entry", name);
		assertEqualIntA(a, err, ARCHIVE_EOF);
		failure("%s: Size returned at EOF must be zero", name);
		assertEqualInt((int)actual.s, 0);
		failure("%s: Offset of final empty chunk must be same as file size", name);
		assertEqualInt(actual.o, expect.o);
		/* Step to next file description. */
		++ac;
	}

	err = archive_read_next_header(a, &ae);
	assertEqualIntA(a, ARCHIVE_EOF, err);

	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}