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
typedef  int /*<<< orphan*/  test_txt ;
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
 int /*<<< orphan*/  archive_entry_symlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_file_count (struct archive*) ; 
 int archive_read_close (struct archive*) ; 
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
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualMem (char*,char const*,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_reference_files (char const**) ; 

__attribute__((used)) static void
test_splitted_file(void)
{
  char buff[64];
  static const char *reffiles[] =
  {
    "test_read_splitted_rar_aa",
    "test_read_splitted_rar_ab",
    "test_read_splitted_rar_ac",
    "test_read_splitted_rar_ad",
    NULL
  };
  const char test_txt[] = "test text document\r\n";
  int size = sizeof(test_txt)-1;
  struct archive_entry *ae;
  struct archive *a;

  extract_reference_files(reffiles);
  assert((a = archive_read_new()) != NULL);
  assertA(0 == archive_read_support_filter_all(a));
  assertA(0 == archive_read_support_format_all(a));
  assertA(0 == archive_read_open_filenames(a, reffiles, 10240));

  /* First header. */
  assertA(0 == archive_read_next_header(a, &ae));
  assertEqualString("test.txt", archive_entry_pathname(ae));
  assertA((int)archive_entry_mtime(ae));
  assertA((int)archive_entry_ctime(ae));
  assertA((int)archive_entry_atime(ae));
  assertEqualInt(20, archive_entry_size(ae));
  assertEqualInt(33188, archive_entry_mode(ae));
  assertA(size == archive_read_data(a, buff, size));
  assertEqualMem(buff, test_txt, size);

  /* Second header. */
  assertA(0 == archive_read_next_header(a, &ae));
  assertEqualString("testlink", archive_entry_pathname(ae));
  assertA((int)archive_entry_mtime(ae));
  assertA((int)archive_entry_ctime(ae));
  assertA((int)archive_entry_atime(ae));
  assertEqualInt(0, archive_entry_size(ae));
  assertEqualInt(41471, archive_entry_mode(ae));
  assertEqualString("test.txt", archive_entry_symlink(ae));
  assertEqualIntA(a, 0, archive_read_data(a, buff, sizeof(buff)));

  /* Third header. */
  assertA(0 == archive_read_next_header(a, &ae));
  assertEqualString("testdir/test.txt", archive_entry_pathname(ae));
  assertA((int)archive_entry_mtime(ae));
  assertA((int)archive_entry_ctime(ae));
  assertA((int)archive_entry_atime(ae));
  assertEqualInt(20, archive_entry_size(ae));
  assertEqualInt(33188, archive_entry_mode(ae));
  assertA(size == archive_read_data(a, buff, size));
  assertEqualMem(buff, test_txt, size);

  /* Fourth header. */
  assertA(0 == archive_read_next_header(a, &ae));
  assertEqualString("testdir", archive_entry_pathname(ae));
  assertA((int)archive_entry_mtime(ae));
  assertA((int)archive_entry_ctime(ae));
  assertA((int)archive_entry_atime(ae));
  assertEqualInt(0, archive_entry_size(ae));
  assertEqualInt(16877, archive_entry_mode(ae));

  /* Fifth header. */
  assertA(0 == archive_read_next_header(a, &ae));
  assertEqualString("testemptydir", archive_entry_pathname(ae));
  assertA((int)archive_entry_mtime(ae));
  assertA((int)archive_entry_ctime(ae));
  assertA((int)archive_entry_atime(ae));
  assertEqualInt(0, archive_entry_size(ae));
  assertEqualInt(16877, archive_entry_mode(ae));

  /* Test EOF */
  assertA(1 == archive_read_next_header(a, &ae));
  assertEqualInt(5, archive_file_count(a));
  assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
  assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}