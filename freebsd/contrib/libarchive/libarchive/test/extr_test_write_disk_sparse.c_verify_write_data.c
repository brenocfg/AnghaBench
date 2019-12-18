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
struct stat {size_t st_size; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AE_IFREG ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int) ; 
 char archive_write_data (struct archive*,char*,size_t) ; 
 int /*<<< orphan*/  archive_write_finish_entry (struct archive*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertEqualInt (size_t,char) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualMem (char*,char const*,int) ; 
 int /*<<< orphan*/  failure (char*,...) ; 
 char fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 char fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void
verify_write_data(struct archive *a, int sparse)
{
	static const char data[]="abcdefghijklmnopqrstuvwxyz";
	struct stat st;
	struct archive_entry *ae;
	size_t buff_size = 64 * 1024;
	char *buff, *p;
	const char *msg = sparse ? "sparse" : "non-sparse";
	FILE *f;

	buff = malloc(buff_size);
	assert(buff != NULL);
	if (buff == NULL)
		return;

	ae = archive_entry_new();
	assert(ae != NULL);
	archive_entry_set_size(ae, 8 * buff_size);
	archive_entry_set_pathname(ae, "test_write_data");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	assertEqualIntA(a, 0, archive_write_header(a, ae));

	/* Use archive_write_data() to write three relatively sparse blocks. */

	/* First has non-null data at beginning. */
	memset(buff, 0, buff_size);
	memcpy(buff, data, sizeof(data));
	failure("%s", msg);
	assertEqualInt(buff_size, archive_write_data(a, buff, buff_size));

	/* Second has non-null data in the middle. */
	memset(buff, 0, buff_size);
	memcpy(buff + buff_size / 2 - 3, data, sizeof(data));
	failure("%s", msg);
	assertEqualInt(buff_size, archive_write_data(a, buff, buff_size));

	/* Third has non-null data at the end. */
	memset(buff, 0, buff_size);
	memcpy(buff + buff_size - sizeof(data), data, sizeof(data));
	failure("%s", msg);
	assertEqualInt(buff_size, archive_write_data(a, buff, buff_size));

	failure("%s", msg);
	assertEqualIntA(a, 0, archive_write_finish_entry(a));

	/* Test the entry on disk. */
	assert(0 == stat(archive_entry_pathname(ae), &st));
        assertEqualInt(st.st_size, 8 * buff_size);
	f = fopen(archive_entry_pathname(ae), "rb");
	assert(f != NULL);
	if (f == NULL) {
		free(buff);
		return;
	}

	/* Check first block. */
	assertEqualInt(buff_size, fread(buff, 1, buff_size, f));
	failure("%s", msg);
	assertEqualMem(buff, data, sizeof(data));
	for (p = buff + sizeof(data); p < buff + buff_size; ++p) {
		failure("offset: %d, %s", (int)(p - buff), msg);
		if (!assertEqualInt(0, *p))
			break;
	}

	/* Check second block. */
	assertEqualInt(buff_size, fread(buff, 1, buff_size, f));
	for (p = buff; p < buff + buff_size; ++p) {
		failure("offset: %d, %s", (int)(p - buff), msg);
		if (p == buff + buff_size / 2 - 3) {
			assertEqualMem(p, data, sizeof(data));
			p += sizeof(data);
		} else if (!assertEqualInt(0, *p))
			break;
	}

	/* Check third block. */
	assertEqualInt(buff_size, fread(buff, 1, buff_size, f));
	for (p = buff; p < buff + buff_size - sizeof(data); ++p) {
		failure("offset: %d, %s", (int)(p - buff), msg);
		if (!assertEqualInt(0, *p))
			break;
	}
	failure("%s", msg);
	assertEqualMem(buff + buff_size - sizeof(data), data, sizeof(data));

	/* XXX more XXX */

	assertEqualInt(0, fclose(f));
	archive_entry_free(ae);
	free(buff);
}