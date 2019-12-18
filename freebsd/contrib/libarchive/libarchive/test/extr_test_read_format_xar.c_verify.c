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
typedef  struct archive archive ;
typedef  enum enc { ____Placeholder_enc } enc ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 scalar_t__ ARCHIVE_FILTER_NONE ; 
 scalar_t__ ARCHIVE_FORMAT_XAR ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED ; 
 int ARCHIVE_WARN ; 
#define  BZIP2 129 
#define  GZIP 128 
 int archive_entry_is_encrypted (struct archive_entry*) ; 
 scalar_t__ archive_file_count (struct archive*) ; 
 int archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 scalar_t__ archive_read_free (struct archive*) ; 
 int archive_read_has_encrypted_entries (struct archive*) ; 
 struct archive* archive_read_new () ; 
 scalar_t__ archive_read_next_header (struct archive*,struct archive_entry**) ; 
 scalar_t__ archive_read_open_memory (struct archive*,unsigned char*,size_t) ; 
 scalar_t__ archive_read_support_filter_all (struct archive*) ; 
 int archive_read_support_filter_bzip2 (struct archive*) ; 
 scalar_t__ archive_read_support_format_all (struct archive*) ; 
 int archive_read_support_format_xar (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,scalar_t__) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skipping (char*) ; 

__attribute__((used)) static void verify(unsigned char *d, size_t s,
    void (*f1)(struct archive *, struct archive_entry *),
    void (*f2)(struct archive *, struct archive_entry *),
    enum enc etype)
{
	struct archive_entry *ae;
	struct archive *a;
	unsigned char *buff;
	int r;

	assert((a = archive_read_new()) != NULL);
	switch (etype) {
	case BZIP2:
		/* This is only check whether bzip is supported or not.
		 * This filter won't be used this test.  */
		if (ARCHIVE_OK != archive_read_support_filter_bzip2(a)) {
			skipping("Unsupported bzip2");
			assertEqualInt(ARCHIVE_OK, archive_read_free(a));
			return;
		}
		break;
	case GZIP:
		/* This gzip must be needed. archive_read_support_format_xar()
		 * will return a warning if gzip is unsupported. */
		break;
	}
	assertA(0 == archive_read_support_filter_all(a));
	r = archive_read_support_format_xar(a);
	if (r == ARCHIVE_WARN) {
		skipping("xar reading not fully supported on this platform");
		assertEqualInt(ARCHIVE_OK, archive_read_free(a));
		return;
	}
	assert((buff = malloc(100000)) != NULL);
	if (buff == NULL)
		return;
	memcpy(buff, d, s);
	memset(buff + s, 0, 2048);

	assertA(0 == archive_read_support_format_all(a));
	assertA(0 == archive_read_open_memory(a, buff, s + 1024));
	assertA(0 == archive_read_next_header(a, &ae));
	assertEqualInt(archive_filter_code(a, 0), ARCHIVE_FILTER_NONE);
	assertEqualInt(archive_format(a), ARCHIVE_FORMAT_XAR);
	assertEqualInt(archive_entry_is_encrypted(ae), 0);
	assertEqualIntA(a, archive_read_has_encrypted_entries(a), ARCHIVE_READ_FORMAT_ENCRYPTION_UNSUPPORTED);
	/* Verify the only entry. */
	f1(a, ae);
	if (f2) {
		assertA(0 == archive_read_next_header(a, &ae));
		assertEqualInt(archive_filter_code(a, 0), ARCHIVE_FILTER_NONE);
		assertEqualInt(archive_format(a), ARCHIVE_FORMAT_XAR);
		/* Verify the only entry. */
		f2(a, ae);
		assertEqualInt(2, archive_file_count(a));
	} else {
		assertEqualInt(1, archive_file_count(a));
	}
	/* End of archive. */
	assertEqualInt(ARCHIVE_EOF, archive_read_next_header(a, &ae));

	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
	free(buff);
}