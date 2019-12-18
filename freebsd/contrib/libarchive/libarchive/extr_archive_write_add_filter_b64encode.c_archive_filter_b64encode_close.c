#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  s; } ;
struct private_b64encode {scalar_t__ hold_len; TYPE_1__ encoded_buff; int /*<<< orphan*/  hold; } ;
struct archive_write_filter {int /*<<< orphan*/  next_filter; int /*<<< orphan*/  archive; scalar_t__ data; } ;

/* Variables and functions */
 int __archive_write_close_filter (int /*<<< orphan*/ ) ; 
 int __archive_write_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_sprintf (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  archive_strlen (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_write_set_bytes_in_last_block (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  la_b64_encode (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
archive_filter_b64encode_close(struct archive_write_filter *f)
{
	struct private_b64encode *state = (struct private_b64encode *)f->data;
	int ret, ret2;

	/* Flush remaining bytes. */
	if (state->hold_len != 0)
		la_b64_encode(&state->encoded_buff, state->hold, state->hold_len);
	archive_string_sprintf(&state->encoded_buff, "====\n");
	/* Write the last block */
	archive_write_set_bytes_in_last_block(f->archive, 1);
	ret = __archive_write_filter(f->next_filter,
	    state->encoded_buff.s, archive_strlen(&state->encoded_buff));
	ret2 = __archive_write_close_filter(f->next_filter);
	if (ret > ret2)
		ret = ret2;
	return (ret);
}