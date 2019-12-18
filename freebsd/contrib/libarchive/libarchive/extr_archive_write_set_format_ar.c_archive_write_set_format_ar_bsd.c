#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {TYPE_1__ archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_FORMAT_AR_BSD ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int archive_write_set_format_ar (struct archive_write*) ; 

int
archive_write_set_format_ar_bsd(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	int r;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_ar_bsd");
	r = archive_write_set_format_ar(a);
	if (r == ARCHIVE_OK) {
		a->archive.archive_format = ARCHIVE_FORMAT_AR_BSD;
		a->archive.archive_format_name = "ar (BSD)";
	}
	return (r);
}