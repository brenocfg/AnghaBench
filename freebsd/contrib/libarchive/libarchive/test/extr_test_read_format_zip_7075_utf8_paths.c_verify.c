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
 int /*<<< orphan*/  ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_OK ; 
 char* archive_entry_pathname_utf8 (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualUTF8String (char const*,char*) ; 

__attribute__((used)) static void
verify(struct archive *a) {
	struct archive_entry *ae;
	const char *p;

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assert((p = archive_entry_pathname_utf8(ae)) != NULL);
	assertEqualUTF8String(p, "File 1.txt");

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assert((p = archive_entry_pathname_utf8(ae)) != NULL);
#if defined(__APPLE__)
	/* Compare NFD string. */
	assertEqualUTF8String(p, "File 2 - o\xCC\x88.txt");
#else
	/* Compare NFC string. */
	assertEqualUTF8String(p, "File 2 - \xC3\xB6.txt");
#endif

	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assert((p = archive_entry_pathname_utf8(ae)) != NULL);
#if defined(__APPLE__)
	/* Compare NFD string. */
	assertEqualUTF8String(p, "File 3 - a\xCC\x88.txt");
#else
	/* Compare NFC string. */
	assertEqualUTF8String(p, "File 3 - \xC3\xA4.txt");
#endif

	/* The CRC of the filename fails, so fall back to CDE. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assert((p = archive_entry_pathname_utf8(ae)) != NULL);
	assertEqualUTF8String(p, "File 4 - xx.txt");

	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
}