#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct TYPE_5__ {unsigned char* next_out; unsigned long avail_out; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 int Z_OK ; 
 int Z_STREAM_END ; 
 int git_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr (void*,char,int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,void*,int) ; 
 int unpack_loose_short_header (TYPE_1__*,unsigned char*,unsigned long,void*,unsigned long) ; 

__attribute__((used)) static int unpack_loose_header_to_strbuf(git_zstream *stream, unsigned char *map,
					 unsigned long mapsize, void *buffer,
					 unsigned long bufsiz, struct strbuf *header)
{
	int status;

	status = unpack_loose_short_header(stream, map, mapsize, buffer, bufsiz);
	if (status < Z_OK)
		return -1;

	/*
	 * Check if entire header is unpacked in the first iteration.
	 */
	if (memchr(buffer, '\0', stream->next_out - (unsigned char *)buffer))
		return 0;

	/*
	 * buffer[0..bufsiz] was not large enough.  Copy the partial
	 * result out to header, and then append the result of further
	 * reading the stream.
	 */
	strbuf_add(header, buffer, stream->next_out - (unsigned char *)buffer);
	stream->next_out = buffer;
	stream->avail_out = bufsiz;

	do {
		status = git_inflate(stream, 0);
		strbuf_add(header, buffer, stream->next_out - (unsigned char *)buffer);
		if (memchr(buffer, '\0', stream->next_out - (unsigned char *)buffer))
			return 0;
		stream->next_out = buffer;
		stream->avail_out = bufsiz;
	} while (status != Z_STREAM_END);
	return -1;
}