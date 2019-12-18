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
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 scalar_t__ archive_entry_atime (struct archive_entry*) ; 
 scalar_t__ archive_entry_ctime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 scalar_t__ archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_file_count (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int archive_read_data (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 scalar_t__ archive_read_open_filenames (struct archive*,char const**,int) ; 
 scalar_t__ archive_read_support_filter_all (struct archive*) ; 
 scalar_t__ archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualMem (char*,char const*,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_reference_files (char const**) ; 

__attribute__((used)) static void
test_large_splitted_file(void)
{
  static const char *reffiles[] =
  {
    "test_read_large_splitted_rar_aa",
    "test_read_large_splitted_rar_ab",
    "test_read_large_splitted_rar_ac",
    "test_read_large_splitted_rar_ad",
    "test_read_large_splitted_rar_ae",
    NULL
  };
  const char test_txt[] = "gin-bottom: 0in\"><BR>\n</P>\n</BODY>\n</HTML>";
  int size = 241647978, offset = 0;
  char buff[64];
  struct archive_entry *ae;
  struct archive *a;

  extract_reference_files(reffiles);
  assert((a = archive_read_new()) != NULL);
  assertA(0 == archive_read_support_filter_all(a));
  assertA(0 == archive_read_support_format_all(a));
  assertA(0 == archive_read_open_filenames(a, reffiles, 10240));

  /* First header. */
  assertA(0 == archive_read_next_header(a, &ae));
  assertEqualString("ppmd_lzss_conversion_test.txt",
                    archive_entry_pathname(ae));
  assertA((int)archive_entry_mtime(ae));
  assertA((int)archive_entry_ctime(ae));
  assertA((int)archive_entry_atime(ae));
  assertEqualInt(size, archive_entry_size(ae));
  assertEqualInt(33188, archive_entry_mode(ae));
  while (offset + (int)sizeof(buff) < size)
  {
    assertA(sizeof(buff) == archive_read_data(a, buff, sizeof(buff)));
    offset += sizeof(buff);
  }
  assertA(size - offset == archive_read_data(a, buff, size - offset));
  assertEqualMem(buff, test_txt, size - offset);

  /* Test EOF */
  assertA(1 == archive_read_next_header(a, &ae));
  assertEqualInt(1, archive_file_count(a));
  assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
  assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}