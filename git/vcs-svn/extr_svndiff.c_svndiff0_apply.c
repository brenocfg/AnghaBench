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
struct sliding_view {int dummy; } ;
struct line_buffer {int dummy; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ apply_one_window (struct line_buffer*,scalar_t__*,struct sliding_view*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ move_window (struct sliding_view*,scalar_t__,size_t) ; 
 scalar_t__ read_length (struct line_buffer*,size_t*,scalar_t__*) ; 
 scalar_t__ read_magic (struct line_buffer*,scalar_t__*) ; 
 scalar_t__ read_offset (struct line_buffer*,scalar_t__*,scalar_t__*) ; 

int svndiff0_apply(struct line_buffer *delta, off_t delta_len,
			struct sliding_view *preimage, FILE *postimage)
{
	assert(delta && preimage && postimage && delta_len >= 0);

	if (read_magic(delta, &delta_len))
		return -1;
	while (delta_len) {	/* For each window: */
		off_t pre_off = -1;
		size_t pre_len;

		if (read_offset(delta, &pre_off, &delta_len) ||
		    read_length(delta, &pre_len, &delta_len) ||
		    move_window(preimage, pre_off, pre_len) ||
		    apply_one_window(delta, &delta_len, preimage, postimage))
			return -1;
	}
	return 0;
}