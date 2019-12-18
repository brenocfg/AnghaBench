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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 

__attribute__((used)) static bool
allzeros(const void *data, size_t size)
{
	const uint64_t *p = data;
	unsigned int i;
	uint64_t v;

	PJDLOG_ASSERT((size % sizeof(*p)) == 0);

	/*
	 * This is the fastest method I found for checking if the given
	 * buffer contain all zeros.
	 * Because inside the loop we don't check at every step, we would
	 * get an answer only after walking through entire buffer.
	 * To return early if the buffer doesn't contain all zeros, we probe
	 * 8 bytes at the beginning, in the middle and at the end of the buffer
	 * first.
	 */

	size >>= 3;	/* divide by 8 */
	if ((p[0] | p[size >> 1] | p[size - 1]) != 0)
		return (false);
	v = 0;
	for (i = 0; i < size; i++)
		v |= *p++;
	return (v == 0);
}