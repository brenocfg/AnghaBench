#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* boot; } ;
struct iso9660 {TYPE_4__ el_torito; } ;
struct archive_write {int /*<<< orphan*/  archive; struct iso9660* format_data; } ;
struct TYPE_7__ {TYPE_2__* file; } ;
struct TYPE_5__ {scalar_t__ header_size; } ;
struct TYPE_6__ {TYPE_1__ zisofs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
zisofs_rewind_boot_file(struct archive_write *a)
{
	struct iso9660 *iso9660 = a->format_data;

	if (iso9660->el_torito.boot->file->zisofs.header_size != 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "We cannot extract the zisofs imaged boot file;"
		    " this may not boot in being zisofs imaged");
		return (ARCHIVE_FAILED);
	}
	return (ARCHIVE_OK);
}