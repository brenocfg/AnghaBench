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
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {size_t len; size_t offset; size_t data; scalar_t__ cb_data; } ;
typedef  TYPE_1__ gitno_buffer ;
typedef  int /*<<< orphan*/  git_stream ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ git_stream_read (int /*<<< orphan*/ *,size_t,int) ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recv_stream(gitno_buffer *buf)
{
	git_stream *io = (git_stream *) buf->cb_data;
	size_t readlen = buf->len - buf->offset;
	ssize_t ret;

	readlen = min(readlen, INT_MAX);

	ret = git_stream_read(io, buf->data + buf->offset, (int)readlen);
	if (ret < 0)
		return -1;

	buf->offset += ret;
	return (int)ret;
}