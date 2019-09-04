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
struct buf_stream {int /*<<< orphan*/ * target; TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  buf_stream_close ; 
 int /*<<< orphan*/  buf_stream_free ; 
 int /*<<< orphan*/  buf_stream_write ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct buf_stream*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void buf_stream_init(struct buf_stream *writer, git_buf *target)
{
	memset(writer, 0, sizeof(struct buf_stream));

	writer->parent.write = buf_stream_write;
	writer->parent.close = buf_stream_close;
	writer->parent.free = buf_stream_free;
	writer->target = target;

	git_buf_clear(target);
}