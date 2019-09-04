#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct buf_stream {int /*<<< orphan*/  complete; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  git_filter_list ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_stream_init (struct buf_stream*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_attach_notowned (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_sanitize (TYPE_1__*) ; 
 int git_filter_list_stream_data (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

int git_filter_list_apply_to_data(
	git_buf *tgt, git_filter_list *filters, git_buf *src)
{
	struct buf_stream writer;
	int error;

	git_buf_sanitize(tgt);
	git_buf_sanitize(src);

	if (!filters) {
		git_buf_attach_notowned(tgt, src->ptr, src->size);
		return 0;
	}

	buf_stream_init(&writer, tgt);

	if ((error = git_filter_list_stream_data(filters, src,
		&writer.parent)) < 0)
			return error;

	assert(writer.complete);
	return error;
}