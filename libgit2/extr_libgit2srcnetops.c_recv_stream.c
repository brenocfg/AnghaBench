#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ offset; scalar_t__ len; scalar_t__ data; scalar_t__ cb_data; } ;
typedef  TYPE_1__ gitno_buffer ;
typedef  int /*<<< orphan*/  git_stream ;

/* Variables and functions */
 int git_stream_read (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int recv_stream(gitno_buffer *buf)
{
	git_stream *io = (git_stream *) buf->cb_data;
	int ret;

	ret = git_stream_read(io, buf->data + buf->offset, buf->len - buf->offset);
	if (ret < 0)
		return -1;

	buf->offset += ret;
	return ret;
}