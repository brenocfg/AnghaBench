#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  u8; } ;
typedef  TYPE_1__ io_buf ;
struct TYPE_8__ {scalar_t__ dest_pending_sparse; int /*<<< orphan*/  dest_name; int /*<<< orphan*/  dest_fd; scalar_t__ dest_try_sparse; } ;
typedef  TYPE_2__ file_pair ;

/* Variables and functions */
 size_t IO_BUFFER_SIZE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int io_write_buf (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ is_sparse (TYPE_1__ const*) ; 
 int lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

extern bool
io_write(file_pair *pair, const io_buf *buf, size_t size)
{
	assert(size <= IO_BUFFER_SIZE);

	if (pair->dest_try_sparse) {
		// Check if the block is sparse (contains only zeros). If it
		// sparse, we just store the amount and return. We will take
		// care of actually skipping over the hole when we hit the
		// next data block or close the file.
		//
		// Since io_close() requires that dest_pending_sparse > 0
		// if the file ends with sparse block, we must also return
		// if size == 0 to avoid doing the lseek().
		if (size == IO_BUFFER_SIZE) {
			if (is_sparse(buf)) {
				pair->dest_pending_sparse += size;
				return false;
			}
		} else if (size == 0) {
			return false;
		}

		// This is not a sparse block. If we have a pending hole,
		// skip it now.
		if (pair->dest_pending_sparse > 0) {
			if (lseek(pair->dest_fd, pair->dest_pending_sparse,
					SEEK_CUR) == -1) {
				message_error(_("%s: Seeking failed when "
						"trying to create a sparse "
						"file: %s"), pair->dest_name,
						strerror(errno));
				return true;
			}

			pair->dest_pending_sparse = 0;
		}
	}

	return io_write_buf(pair, buf->u8, size);
}