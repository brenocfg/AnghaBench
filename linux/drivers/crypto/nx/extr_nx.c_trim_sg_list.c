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
struct nx_sg {unsigned int len; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int abs (long) ; 

__attribute__((used)) static long int trim_sg_list(struct nx_sg *sg,
			     struct nx_sg *end,
			     unsigned int delta,
			     unsigned int *nbytes)
{
	long int oplen;
	long int data_back;
	unsigned int is_delta = delta;

	while (delta && end > sg) {
		struct nx_sg *last = end - 1;

		if (last->len > delta) {
			last->len -= delta;
			delta = 0;
		} else {
			end--;
			delta -= last->len;
		}
	}

	/* There are cases where we need to crop list in order to make it
	 * a block size multiple, but we also need to align data. In order to
	 * that we need to calculate how much we need to put back to be
	 * processed
	 */
	oplen = (sg - end) * sizeof(struct nx_sg);
	if (is_delta) {
		data_back = (abs(oplen) / AES_BLOCK_SIZE) *  sg->len;
		data_back = *nbytes - (data_back & ~(AES_BLOCK_SIZE - 1));
		*nbytes -= data_back;
	}

	return oplen;
}