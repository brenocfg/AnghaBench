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
struct archive_read {TYPE_1__* format; int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_2__ {int (* read_data ) (struct archive_read*,void const**,size_t*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_PROGRAMMER ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_READ_MAGIC ; 
 int /*<<< orphan*/  ARCHIVE_STATE_DATA ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct archive_read*,void const**,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_archive_read_data_block(struct archive *_a,
    const void **buff, size_t *size, int64_t *offset)
{
	struct archive_read *a = (struct archive_read *)_a;
	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_DATA,
	    "archive_read_data_block");

	if (a->format->read_data == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "Internal error: "
		    "No format->read_data function registered");
		return (ARCHIVE_FATAL);
	}

	return (a->format->read_data)(a, buff, size, offset);
}