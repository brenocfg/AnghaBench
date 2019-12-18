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
struct compress_stream {scalar_t__ current_chunk; char current; TYPE_1__* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (TYPE_1__*,char*,int) ;} ;

/* Variables and functions */
 scalar_t__ CHUNKSIZE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*,int) ; 

__attribute__((used)) static int compress_stream_write__deflated(struct compress_stream *stream, const char *buffer, size_t len)
{
	size_t idx = 0;

	while (len > 0) {
		size_t chunkremain, chunksize;

		if (stream->current_chunk == 0)
			stream->current = buffer[idx];

		chunkremain = CHUNKSIZE - stream->current_chunk;
		chunksize = min(chunkremain, len);

		stream->current_chunk += chunksize;
		len -= chunksize;
		idx += chunksize;

		if (stream->current_chunk == CHUNKSIZE) {
			cl_git_pass(stream->next->write(stream->next, &stream->current, 1));
			stream->current_chunk = 0;
		}
	}

	return 0;
}