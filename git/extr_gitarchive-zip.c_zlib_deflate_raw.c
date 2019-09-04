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
struct TYPE_6__ {unsigned long avail_in; unsigned long avail_out; unsigned long total_out; void* next_out; void* next_in; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 int /*<<< orphan*/  Z_FINISH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  free (void*) ; 
 int git_deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned long git_deflate_bound (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  git_deflate_end (TYPE_1__*) ; 
 int /*<<< orphan*/  git_deflate_init_raw (TYPE_1__*,int) ; 
 void* xmalloc (unsigned long) ; 

__attribute__((used)) static void *zlib_deflate_raw(void *data, unsigned long size,
			      int compression_level,
			      unsigned long *compressed_size)
{
	git_zstream stream;
	unsigned long maxsize;
	void *buffer;
	int result;

	git_deflate_init_raw(&stream, compression_level);
	maxsize = git_deflate_bound(&stream, size);
	buffer = xmalloc(maxsize);

	stream.next_in = data;
	stream.avail_in = size;
	stream.next_out = buffer;
	stream.avail_out = maxsize;

	do {
		result = git_deflate(&stream, Z_FINISH);
	} while (result == Z_OK);

	if (result != Z_STREAM_END) {
		free(buffer);
		return NULL;
	}

	git_deflate_end(&stream);
	*compressed_size = stream.total_out;

	return buffer;
}