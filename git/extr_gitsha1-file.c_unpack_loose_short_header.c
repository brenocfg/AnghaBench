#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned char* next_in; unsigned long avail_in; unsigned long avail_out; void* next_out; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 int git_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_inflate_init (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int unpack_loose_short_header(git_zstream *stream,
				     unsigned char *map, unsigned long mapsize,
				     void *buffer, unsigned long bufsiz)
{
	/* Get the data stream */
	memset(stream, 0, sizeof(*stream));
	stream->next_in = map;
	stream->avail_in = mapsize;
	stream->next_out = buffer;
	stream->avail_out = bufsiz;

	git_inflate_init(stream);
	return git_inflate(stream, 0);
}