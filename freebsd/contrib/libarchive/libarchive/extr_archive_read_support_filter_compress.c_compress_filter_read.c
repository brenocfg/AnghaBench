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
struct private_data {int end_of_stream; int out_block_size; int /*<<< orphan*/ * stackp; int /*<<< orphan*/ * stack; scalar_t__ out_block; } ;
struct archive_read_filter {scalar_t__ data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int next_code (struct archive_read_filter*) ; 

__attribute__((used)) static ssize_t
compress_filter_read(struct archive_read_filter *self, const void **pblock)
{
	struct private_data *state;
	unsigned char *p, *start, *end;
	int ret;

	state = (struct private_data *)self->data;
	if (state->end_of_stream) {
		*pblock = NULL;
		return (0);
	}
	p = start = (unsigned char *)state->out_block;
	end = start + state->out_block_size;

	while (p < end && !state->end_of_stream) {
		if (state->stackp > state->stack) {
			*p++ = *--state->stackp;
		} else {
			ret = next_code(self);
			if (ret == -1)
				state->end_of_stream = ret;
			else if (ret != ARCHIVE_OK)
				return (ret);
		}
	}

	*pblock = start;
	return (p - start);
}