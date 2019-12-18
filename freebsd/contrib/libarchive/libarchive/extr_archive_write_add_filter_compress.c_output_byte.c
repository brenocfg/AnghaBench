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
struct private_data {unsigned char* compressed; scalar_t__ compressed_offset; scalar_t__ compressed_buffer_size; int /*<<< orphan*/  out_count; } ;
struct archive_write_filter {int /*<<< orphan*/  next_filter; struct private_data* data; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int __archive_write_filter (int /*<<< orphan*/ ,unsigned char*,scalar_t__) ; 

__attribute__((used)) static int
output_byte(struct archive_write_filter *f, unsigned char c)
{
	struct private_data *state = f->data;

	state->compressed[state->compressed_offset++] = c;
	++state->out_count;

	if (state->compressed_buffer_size == state->compressed_offset) {
		int ret = __archive_write_filter(f->next_filter,
		    state->compressed, state->compressed_buffer_size);
		if (ret != ARCHIVE_OK)
			return ARCHIVE_FATAL;
		state->compressed_offset = 0;
	}

	return ARCHIVE_OK;
}