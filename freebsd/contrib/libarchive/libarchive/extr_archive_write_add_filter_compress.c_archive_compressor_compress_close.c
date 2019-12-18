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
struct private_data {struct private_data* compressed; int /*<<< orphan*/  compressed_offset; int /*<<< orphan*/  cur_code; } ;
struct archive_write_filter {int /*<<< orphan*/  next_filter; scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int __archive_write_close_filter (int /*<<< orphan*/ ) ; 
 int __archive_write_filter (int /*<<< orphan*/ ,struct private_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct private_data*) ; 
 int output_code (struct archive_write_filter*,int /*<<< orphan*/ ) ; 
 int output_flush (struct archive_write_filter*) ; 

__attribute__((used)) static int
archive_compressor_compress_close(struct archive_write_filter *f)
{
	struct private_data *state = (struct private_data *)f->data;
	int ret, ret2;

	ret = output_code(f, state->cur_code);
	if (ret != ARCHIVE_OK)
		goto cleanup;
	ret = output_flush(f);
	if (ret != ARCHIVE_OK)
		goto cleanup;

	/* Write the last block */
	ret = __archive_write_filter(f->next_filter,
	    state->compressed, state->compressed_offset);
cleanup:
	ret2 = __archive_write_close_filter(f->next_filter);
	if (ret > ret2)
		ret = ret2;
	free(state->compressed);
	free(state);
	return (ret);
}