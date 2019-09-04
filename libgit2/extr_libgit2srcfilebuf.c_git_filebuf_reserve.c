#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t buf_size; size_t buf_pos; void* buffer; int /*<<< orphan*/  last_error; } ;
typedef  TYPE_1__ git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  BUFERR_MEM ; 
 int /*<<< orphan*/  ENSURE_BUF_OK (TYPE_1__*) ; 
 scalar_t__ flush_buffer (TYPE_1__*) ; 

int git_filebuf_reserve(git_filebuf *file, void **buffer, size_t len)
{
	size_t space_left = file->buf_size - file->buf_pos;

	*buffer = NULL;

	ENSURE_BUF_OK(file);

	if (len > file->buf_size) {
		file->last_error = BUFERR_MEM;
		return -1;
	}

	if (space_left <= len) {
		if (flush_buffer(file) < 0)
			return -1;
	}

	*buffer = (file->buffer + file->buf_pos);
	file->buf_pos += len;

	return 0;
}