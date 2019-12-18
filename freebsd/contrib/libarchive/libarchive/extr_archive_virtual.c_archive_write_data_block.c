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
struct archive {TYPE_1__* vtable; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  la_ssize_t ;
typedef  int /*<<< orphan*/  la_int64_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* archive_write_data_block ) (struct archive*,void const*,size_t,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int /*<<< orphan*/  ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_STATE_FATAL ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct archive*,void const*,size_t,int /*<<< orphan*/ ) ; 

la_ssize_t
archive_write_data_block(struct archive *a, const void *buff, size_t s,
    la_int64_t o)
{
	if (a->vtable->archive_write_data_block == NULL) {
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "archive_write_data_block not supported");
		a->state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}
	return ((a->vtable->archive_write_data_block)(a, buff, s, o));
}