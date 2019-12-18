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
struct TYPE_2__ {size_t start_len; size_t start_read; size_t start; int /*<<< orphan*/  zstream; } ;
typedef  TYPE_1__ loose_readstream ;
typedef  int /*<<< orphan*/  git_odb_stream ;

/* Variables and functions */
 size_t INT_MAX ; 
 int git_zstream_get_output (char*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,size_t,size_t) ; 
 size_t min (size_t,size_t) ; 

__attribute__((used)) static int loose_backend__readstream_read(
	git_odb_stream *_stream,
	char *buffer,
	size_t buffer_len)
{
	loose_readstream *stream = (loose_readstream *)_stream;
	size_t start_remain = stream->start_len - stream->start_read;
	int total = 0, error;

	buffer_len = min(buffer_len, INT_MAX);

	/*
	 * if we read more than just the header in the initial read, play
	 * that back for the caller.
	 */
	if (start_remain && buffer_len) {
		size_t chunk = min(start_remain, buffer_len);
		memcpy(buffer, stream->start + stream->start_read, chunk);

		buffer += chunk;
		stream->start_read += chunk;

		total += (int)chunk;
		buffer_len -= chunk;
	}

	if (buffer_len) {
		size_t chunk = buffer_len;

		if ((error = git_zstream_get_output(buffer, &chunk, &stream->zstream)) < 0)
			return error;

		total += (int)chunk;
	}

	return (int)total;
}