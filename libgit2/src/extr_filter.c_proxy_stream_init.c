#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  free; int /*<<< orphan*/  close; int /*<<< orphan*/  write; } ;
struct proxy_stream {void** payload; int /*<<< orphan*/  temp_buf; int /*<<< orphan*/ * output; int /*<<< orphan*/ * target; int /*<<< orphan*/  const* source; int /*<<< orphan*/ * filter; TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  git_writestream ;
typedef  int /*<<< orphan*/  git_filter_source ;
typedef  int /*<<< orphan*/  git_filter ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct proxy_stream*) ; 
 struct proxy_stream* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proxy_stream_close ; 
 int /*<<< orphan*/  proxy_stream_free ; 
 int /*<<< orphan*/  proxy_stream_write ; 

__attribute__((used)) static int proxy_stream_init(
	git_writestream **out,
	git_filter *filter,
	git_buf *temp_buf,
	void **payload,
	const git_filter_source *source,
	git_writestream *target)
{
	struct proxy_stream *proxy_stream = git__calloc(1, sizeof(struct proxy_stream));
	GIT_ERROR_CHECK_ALLOC(proxy_stream);

	proxy_stream->parent.write = proxy_stream_write;
	proxy_stream->parent.close = proxy_stream_close;
	proxy_stream->parent.free = proxy_stream_free;
	proxy_stream->filter = filter;
	proxy_stream->payload = payload;
	proxy_stream->source = source;
	proxy_stream->target = target;
	proxy_stream->output = temp_buf ? temp_buf : &proxy_stream->temp_buf;

	if (temp_buf)
		git_buf_clear(temp_buf);

	*out = (git_writestream *)proxy_stream;
	return 0;
}