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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  REALLOC_ARRAY (unsigned char*,size_t) ; 
 size_t alloc_nr (size_t) ; 
 int /*<<< orphan*/  die (char*,size_t) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 size_t max_request_buffer ; 
 scalar_t__ read_in_full (int,unsigned char*,size_t) ; 
 unsigned char* xmalloc (size_t) ; 

__attribute__((used)) static ssize_t read_request_eof(int fd, unsigned char **out)
{
	size_t len = 0, alloc = 8192;
	unsigned char *buf = xmalloc(alloc);

	if (max_request_buffer < alloc)
		max_request_buffer = alloc;

	while (1) {
		ssize_t cnt;

		cnt = read_in_full(fd, buf + len, alloc - len);
		if (cnt < 0) {
			free(buf);
			return -1;
		}

		/* partial read from read_in_full means we hit EOF */
		len += cnt;
		if (len < alloc) {
			*out = buf;
			return len;
		}

		/* otherwise, grow and try again (if we can) */
		if (alloc == max_request_buffer)
			die("request was larger than our maximum size (%lu);"
			    " try setting GIT_HTTP_MAX_REQUEST_BUFFER",
			    max_request_buffer);

		alloc = alloc_nr(alloc);
		if (alloc > max_request_buffer)
			alloc = max_request_buffer;
		REALLOC_ARRAY(buf, alloc);
	}
}