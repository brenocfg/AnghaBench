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
struct raw_info {size_t unconsumed; int end_of_file; size_t offset; } ;
struct archive_read {TYPE_1__* format; } ;
typedef  void* ssize_t ;
typedef  size_t int64_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 void* __archive_read_ahead (struct archive_read*,int,void**) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,size_t) ; 

__attribute__((used)) static int
archive_read_format_raw_read_data(struct archive_read *a,
    const void **buff, size_t *size, int64_t *offset)
{
	struct raw_info *info;
	ssize_t avail;

	info = (struct raw_info *)(a->format->data);

	/* Consume the bytes we read last time. */
	if (info->unconsumed) {
		__archive_read_consume(a, info->unconsumed);
		info->unconsumed = 0;
	}

	if (info->end_of_file)
		return (ARCHIVE_EOF);

	/* Get whatever bytes are immediately available. */
	*buff = __archive_read_ahead(a, 1, &avail);
	if (avail > 0) {
		/* Return the bytes we just read */
		*size = avail;
		*offset = info->offset;
		info->offset += *size;
		info->unconsumed = avail;
		return (ARCHIVE_OK);
	} else if (0 == avail) {
		/* Record and return end-of-file. */
		info->end_of_file = 1;
		*size = 0;
		*offset = info->offset;
		return (ARCHIVE_EOF);
	} else {
		/* Record and return an error. */
		*size = 0;
		*offset = info->offset;
		return ((int)avail);
	}
}