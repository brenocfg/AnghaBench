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
struct cpio {scalar_t__ entry_bytes_remaining; scalar_t__ entry_padding; scalar_t__ entry_bytes_unconsumed; } ;
struct archive_read {TYPE_1__* format; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ __archive_read_consume (struct archive_read*,scalar_t__) ; 

__attribute__((used)) static int
archive_read_format_cpio_skip(struct archive_read *a)
{
	struct cpio *cpio = (struct cpio *)(a->format->data);
	int64_t to_skip = cpio->entry_bytes_remaining + cpio->entry_padding +
		cpio->entry_bytes_unconsumed;

	if (to_skip != __archive_read_consume(a, to_skip)) {
		return (ARCHIVE_FATAL);
	}
	cpio->entry_bytes_remaining = 0;
	cpio->entry_padding = 0;
	cpio->entry_bytes_unconsumed = 0;
	return (ARCHIVE_OK);
}