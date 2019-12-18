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
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_filter_count (struct archive*) ; 
 int archive_write_add_filter_bzip2 (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 struct archive* archive_write_new () ; 
 int /*<<< orphan*/  archive_write_open_memory (struct archive*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_set_bytes_per_block (struct archive*,int) ; 
 int /*<<< orphan*/  archive_write_set_format_ustar (struct archive*) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canBzip2 () ; 
 int /*<<< orphan*/  skipping (char*) ; 

__attribute__((used)) static void
write_test(void)
{
	char buff[4096];
	struct archive* a = archive_write_new();
	int r;

	assertEqualIntA(a, ARCHIVE_OK, archive_write_set_format_ustar(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_write_set_bytes_per_block(a, 10));

	r = archive_write_add_filter_bzip2(a);
	if((ARCHIVE_WARN == r && !canBzip2()) || ARCHIVE_WARN > r) {
		skipping("bzip2 unsupported");
		return;
	}
	assertEqualIntA(a, ARCHIVE_OK, archive_write_open_memory(a, buff, 4096, 0));
	/* bzip2 and none */
	assertEqualInt(2, archive_filter_count(a));
	archive_write_free(a);
}