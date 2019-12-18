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
typedef  struct archive_entry archive_entry ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ; 
 int /*<<< orphan*/  archive_entry_is_encrypted (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int archive_read_free (struct archive*) ; 
 int /*<<< orphan*/  archive_read_has_encrypted_entries (struct archive*) ; 
 struct archive* archive_read_new () ; 
 scalar_t__ archive_read_next_header (struct archive*,struct archive_entry**) ; 
 scalar_t__ archive_read_open_memory (struct archive*,unsigned char*,size_t) ; 
 scalar_t__ archive_read_support_filter_all (struct archive*) ; 
 scalar_t__ archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void verify(unsigned char *d, size_t s,
    void (*f)(struct archive_entry *),
    int compression, int format)
{
	struct archive_entry *ae;
	struct archive *a;
	unsigned char *buff = malloc(100000);

	memcpy(buff, d, s);
	memset(buff + s, 0, 2048);

	assert((a = archive_read_new()) != NULL);
	assertA(0 == archive_read_support_filter_all(a));
	assertA(0 == archive_read_support_format_all(a));
	assertA(0 == archive_read_open_memory(a, buff, s + 1024));
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualInt(archive_filter_code(a, 0), compression);
	assertEqualInt(archive_format(a), format);
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);

	/* Verify the only entry. */
	f(ae);

	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
	free(buff);
}