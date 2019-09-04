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
typedef  int /*<<< orphan*/  stream ;
struct TYPE_6__ {unsigned long avail_out; void* avail_in; unsigned long total_out; void* next_in; void* next_out; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (void*) ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 void* fill (int) ; 
 int git_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_inflate_end (TYPE_1__*) ; 
 int /*<<< orphan*/  git_inflate_init (TYPE_1__*) ; 
 int has_errors ; 
 void* len ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recover ; 
 int /*<<< orphan*/  use (void*) ; 
 void* xmallocz (unsigned long) ; 

__attribute__((used)) static void *get_data(unsigned long size)
{
	git_zstream stream;
	void *buf = xmallocz(size);

	memset(&stream, 0, sizeof(stream));

	stream.next_out = buf;
	stream.avail_out = size;
	stream.next_in = fill(1);
	stream.avail_in = len;
	git_inflate_init(&stream);

	for (;;) {
		int ret = git_inflate(&stream, 0);
		use(len - stream.avail_in);
		if (stream.total_out == size && ret == Z_STREAM_END)
			break;
		if (ret != Z_OK) {
			error("inflate returned %d", ret);
			FREE_AND_NULL(buf);
			if (!recover)
				exit(1);
			has_errors = 1;
			break;
		}
		stream.next_in = fill(1);
		stream.avail_in = len;
	}
	git_inflate_end(&stream);
	return buf;
}