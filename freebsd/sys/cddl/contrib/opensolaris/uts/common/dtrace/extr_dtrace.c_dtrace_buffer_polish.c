#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dtb_flags; scalar_t__ dtb_offset; scalar_t__ dtb_xamot_offset; scalar_t__ dtb_tomax; scalar_t__ dtb_size; } ;
typedef  TYPE_1__ dtrace_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int DTRACEBUF_RING ; 
 int DTRACEBUF_WRAPPED ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dtrace_lock ; 

__attribute__((used)) static void
dtrace_buffer_polish(dtrace_buffer_t *buf)
{
	ASSERT(buf->dtb_flags & DTRACEBUF_RING);
	ASSERT(MUTEX_HELD(&dtrace_lock));

	if (!(buf->dtb_flags & DTRACEBUF_WRAPPED))
		return;

	/*
	 * We need to polish the ring buffer.  There are three cases:
	 *
	 * - The first (and presumably most common) is that there is no gap
	 *   between the buffer offset and the wrapped offset.  In this case,
	 *   there is nothing in the buffer that isn't valid data; we can
	 *   mark the buffer as polished and return.
	 *
	 * - The second (less common than the first but still more common
	 *   than the third) is that there is a gap between the buffer offset
	 *   and the wrapped offset, and the wrapped offset is larger than the
	 *   buffer offset.  This can happen because of an alignment issue, or
	 *   can happen because of a call to dtrace_buffer_reserve() that
	 *   didn't subsequently consume the buffer space.  In this case,
	 *   we need to zero the data from the buffer offset to the wrapped
	 *   offset.
	 *
	 * - The third (and least common) is that there is a gap between the
	 *   buffer offset and the wrapped offset, but the wrapped offset is
	 *   _less_ than the buffer offset.  This can only happen because a
	 *   call to dtrace_buffer_reserve() induced a wrap, but the space
	 *   was not subsequently consumed.  In this case, we need to zero the
	 *   space from the offset to the end of the buffer _and_ from the
	 *   top of the buffer to the wrapped offset.
	 */
	if (buf->dtb_offset < buf->dtb_xamot_offset) {
		bzero(buf->dtb_tomax + buf->dtb_offset,
		    buf->dtb_xamot_offset - buf->dtb_offset);
	}

	if (buf->dtb_offset > buf->dtb_xamot_offset) {
		bzero(buf->dtb_tomax + buf->dtb_offset,
		    buf->dtb_size - buf->dtb_offset);
		bzero(buf->dtb_tomax, buf->dtb_xamot_offset);
	}
}