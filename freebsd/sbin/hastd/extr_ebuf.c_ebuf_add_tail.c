#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ebuf {scalar_t__ eb_magic; scalar_t__ eb_size; scalar_t__ eb_used; scalar_t__ eb_end; } ;

/* Variables and functions */
 scalar_t__ EBUF_MAGIC ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  bcopy (void const*,scalar_t__,size_t) ; 
 int ebuf_tail_extend (struct ebuf*,size_t) ; 

int
ebuf_add_tail(struct ebuf *eb, const void *data, size_t size)
{

	PJDLOG_ASSERT(eb != NULL && eb->eb_magic == EBUF_MAGIC);

	if (size > (size_t)(eb->eb_end - (eb->eb_used + eb->eb_size))) {
		/*
		 * We can't add more entries at the back, so we have to extend
		 * our buffer.
		 */
		if (ebuf_tail_extend(eb, size) == -1)
			return (-1);
	}
	PJDLOG_ASSERT(size <=
	    (size_t)(eb->eb_end - (eb->eb_used + eb->eb_size)));

	/*
	 * If data is NULL the caller just wants to reserve space.
	 */
	if (data != NULL)
		bcopy(data, eb->eb_used + eb->eb_size, size);
	eb->eb_size += size;

	return (0);
}