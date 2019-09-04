#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fuzzer_stream {size_t endp; size_t readp; } ;
typedef  int /*<<< orphan*/  git_smart_subtransport_stream ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,size_t,size_t) ; 

__attribute__((used)) static int fuzzer_stream_read(git_smart_subtransport_stream *stream,
	char *buffer,
	size_t buf_size,
	size_t *bytes_read)
{
	struct fuzzer_stream *fs = (struct fuzzer_stream *) stream;
	size_t avail = fs->endp - fs->readp;

	*bytes_read = (buf_size > avail) ? avail : buf_size;
	memcpy(buffer, fs->readp, *bytes_read);
	fs->readp += *bytes_read;

	return 0;
}