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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int /*<<< orphan*/  ARCHIVE_FATAL ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const void *
cab_read_ahead_cfdata_deflate(struct archive_read *a, ssize_t *avail)
{
	*avail = ARCHIVE_FATAL;
	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
	    "libarchive compiled without deflate support (no libz)");
	return (NULL);
}