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
struct private_data {int bit_offset; int code_len; int /*<<< orphan*/  bit_buf; } ;
struct archive_write_filter {struct private_data* data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int output_byte (struct archive_write_filter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
output_flush(struct archive_write_filter *f)
{
	struct private_data *state = f->data;
	int ret;

	/* At EOF, write the rest of the buffer. */
	if (state->bit_offset % 8) {
		state->code_len = (state->bit_offset % 8 + 7) / 8;
		ret = output_byte(f, state->bit_buf);
		if (ret != ARCHIVE_OK)
			return ret;
	}

	return (ARCHIVE_OK);
}