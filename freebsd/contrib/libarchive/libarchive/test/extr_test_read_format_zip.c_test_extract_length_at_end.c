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
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_OK ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_open_filename (struct archive*,char const*,int) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_reference_file (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  read_open_memory (struct archive*,char*,size_t,int) ; 
 char* slurpfile (size_t*,char const*) ; 
 int /*<<< orphan*/  verify_extract_length_at_end (struct archive*,int) ; 

__attribute__((used)) static void
test_extract_length_at_end(void)
{
	const char *refname = "test_read_format_zip_length_at_end.zip";
	char *p;
	size_t s;
	struct archive *a;

	extract_reference_file(refname);

	/* Verify extraction with seeking reader. */
	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_open_filename(a, refname, 10240));
	verify_extract_length_at_end(a, 1);

	/* Verify extraction with streaming reader. */
	p = slurpfile(&s, refname);
	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	assertEqualIntA(a, ARCHIVE_OK, read_open_memory(a, p, s, 108));
	verify_extract_length_at_end(a, 0);
	free(p);
}