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
struct buf_stream {int /*<<< orphan*/  complete; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  git_filter_list ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_stream_init (struct buf_stream*,int /*<<< orphan*/ *) ; 
 int git_filter_list_stream_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_filter_list_apply_to_blob(
	git_buf *out,
	git_filter_list *filters,
	git_blob *blob)
{
	struct buf_stream writer;
	int error;

	buf_stream_init(&writer, out);

	if ((error = git_filter_list_stream_blob(
		filters, blob, &writer.parent)) < 0)
			return error;

	assert(writer.complete);
	return error;
}