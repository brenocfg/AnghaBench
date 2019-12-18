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
struct archive_write {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
zisofs_write_to_temp(struct archive_write *a, const void *buff, size_t s)
{
	(void)buff; /* UNUSED */
	(void)s; /* UNUSED */
	archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC, "Programming error");
	return (ARCHIVE_FATAL);
}