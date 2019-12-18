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
struct TYPE_2__ {int state; } ;
struct archive_write {int (* format_finish_entry ) (struct archive_write*) ;TYPE_1__ archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_STATE_DATA ; 
 int ARCHIVE_STATE_HEADER ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  archive_check_magic (TYPE_1__*,int /*<<< orphan*/ ,int,char*) ; 
 int stub1 (struct archive_write*) ; 

__attribute__((used)) static int
_archive_write_finish_entry(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	int ret = ARCHIVE_OK;

	archive_check_magic(&a->archive, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
	    "archive_write_finish_entry");
	if (a->archive.state & ARCHIVE_STATE_DATA
	    && a->format_finish_entry != NULL)
		ret = (a->format_finish_entry)(a);
	a->archive.state = ARCHIVE_STATE_HEADER;
	return (ret);
}