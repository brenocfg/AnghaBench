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
struct iso9660 {size_t wbuff_remaining; } ;
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 size_t LOGICAL_BLOCK_SIZE ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wb_write_out (struct archive_write*) ; 

__attribute__((used)) static int
wb_consume(struct archive_write *a, size_t size)
{
	struct iso9660 *iso9660 = (struct iso9660 *)a->format_data;

	if (size > iso9660->wbuff_remaining ||
	    iso9660->wbuff_remaining == 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Internal Programming error: iso9660:wb_consume()"
		    " size=%jd, wbuff_remaining=%jd",
		    (intmax_t)size, (intmax_t)iso9660->wbuff_remaining);
		return (ARCHIVE_FATAL);
	}
	iso9660->wbuff_remaining -= size;
	if (iso9660->wbuff_remaining < LOGICAL_BLOCK_SIZE)
		return (wb_write_out(a));
	return (ARCHIVE_OK);
}