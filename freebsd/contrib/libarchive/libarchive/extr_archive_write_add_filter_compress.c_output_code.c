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
struct private_data {int bit_offset; int bit_buf; int code_len; scalar_t__ first_free; scalar_t__ cur_maxcode; scalar_t__ max_maxcode; } ;
struct archive_write_filter {struct private_data* data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int CLEAR ; 
 void* MAXCODE (int) ; 
 int output_byte (struct archive_write_filter*,int) ; 
 int* rmask ; 

__attribute__((used)) static int
output_code(struct archive_write_filter *f, int ocode)
{
	struct private_data *state = f->data;
	int bits, ret, clear_flg, bit_offset;

	clear_flg = ocode == CLEAR;

	/*
	 * Since ocode is always >= 8 bits, only need to mask the first
	 * hunk on the left.
	 */
	bit_offset = state->bit_offset % 8;
	state->bit_buf |= (ocode << bit_offset) & 0xff;
	output_byte(f, state->bit_buf);

	bits = state->code_len - (8 - bit_offset);
	ocode >>= 8 - bit_offset;
	/* Get any 8 bit parts in the middle (<=1 for up to 16 bits). */
	if (bits >= 8) {
		output_byte(f, ocode & 0xff);
		ocode >>= 8;
		bits -= 8;
	}
	/* Last bits. */
	state->bit_offset += state->code_len;
	state->bit_buf = ocode & rmask[bits];
	if (state->bit_offset == state->code_len * 8)
		state->bit_offset = 0;

	/*
	 * If the next entry is going to be too big for the ocode size,
	 * then increase it, if possible.
	 */
	if (clear_flg || state->first_free > state->cur_maxcode) {
	       /*
		* Write the whole buffer, because the input side won't
		* discover the size increase until after it has read it.
		*/
		if (state->bit_offset > 0) {
			while (state->bit_offset < state->code_len * 8) {
				ret = output_byte(f, state->bit_buf);
				if (ret != ARCHIVE_OK)
					return ret;
				state->bit_offset += 8;
				state->bit_buf = 0;
			}
		}
		state->bit_buf = 0;
		state->bit_offset = 0;

		if (clear_flg) {
			state->code_len = 9;
			state->cur_maxcode = MAXCODE(state->code_len);
		} else {
			state->code_len++;
			if (state->code_len == 16)
				state->cur_maxcode = state->max_maxcode;
			else
				state->cur_maxcode = MAXCODE(state->code_len);
		}
	}

	return (ARCHIVE_OK);
}