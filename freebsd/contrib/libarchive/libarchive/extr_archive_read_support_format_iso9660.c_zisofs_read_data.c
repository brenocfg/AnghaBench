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
struct archive_read {int /*<<< orphan*/  archive; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FAILED ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
zisofs_read_data(struct archive_read *a,
    const void **buff, size_t *size, int64_t *offset)
{

	(void)buff;/* UNUSED */
	(void)size;/* UNUSED */
	(void)offset;/* UNUSED */
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "zisofs is not supported on this platform.");
	return (ARCHIVE_FAILED);
}