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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_errno (struct archive*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int archive_read_data_block (struct archive*,void const**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ archive_write_data_block (struct archive*,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
extract_data(struct archive *ar, struct archive *aw)
{
	int r;
	size_t size;
	const void *block;
	int64_t offset;

	for (;;) {
		r = archive_read_data_block(ar, &block, &size, &offset);
		if (r == ARCHIVE_EOF)
			return (ARCHIVE_OK);
		if (r != ARCHIVE_OK) {
			lafe_warnc(archive_errno(ar),
			    "%s", archive_error_string(ar));
			exit(1);
		}
		r = (int)archive_write_data_block(aw, block, size, offset);
		if (r != ARCHIVE_OK) {
			lafe_warnc(archive_errno(aw),
			    "%s", archive_error_string(aw));
			return (r);
		}
	}
}