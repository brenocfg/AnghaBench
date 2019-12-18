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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  out_buf ;
typedef  int /*<<< orphan*/  in_buf ;
struct TYPE_6__ {unsigned char* next_in; size_t avail_in; unsigned char* next_out; int avail_out; unsigned long total_out; } ;
typedef  TYPE_1__ git_zstream ;

/* Variables and functions */
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int git_inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_inflate_end (TYPE_1__*) ; 
 int /*<<< orphan*/  git_inflate_init_gzip_only (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 size_t read_request (int /*<<< orphan*/ ,unsigned char**,size_t) ; 
 int /*<<< orphan*/  write_to_child (int,unsigned char*,unsigned long,char const*) ; 
 size_t xread (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static void inflate_request(const char *prog_name, int out, int buffer_input, ssize_t req_len)
{
	git_zstream stream;
	unsigned char *full_request = NULL;
	unsigned char in_buf[8192];
	unsigned char out_buf[8192];
	unsigned long cnt = 0;
	int req_len_defined = req_len >= 0;
	size_t req_remaining_len = req_len;

	memset(&stream, 0, sizeof(stream));
	git_inflate_init_gzip_only(&stream);

	while (1) {
		ssize_t n;

		if (buffer_input) {
			if (full_request)
				n = 0; /* nothing left to read */
			else
				n = read_request(0, &full_request, req_len);
			stream.next_in = full_request;
		} else {
			ssize_t buffer_len;
			if (req_len_defined && req_remaining_len <= sizeof(in_buf))
				buffer_len = req_remaining_len;
			else
				buffer_len = sizeof(in_buf);
			n = xread(0, in_buf, buffer_len);
			stream.next_in = in_buf;
			if (req_len_defined && n > 0)
				req_remaining_len -= n;
		}

		if (n <= 0)
			die("request ended in the middle of the gzip stream");
		stream.avail_in = n;

		while (0 < stream.avail_in) {
			int ret;

			stream.next_out = out_buf;
			stream.avail_out = sizeof(out_buf);

			ret = git_inflate(&stream, Z_NO_FLUSH);
			if (ret != Z_OK && ret != Z_STREAM_END)
				die("zlib error inflating request, result %d", ret);

			n = stream.total_out - cnt;
			write_to_child(out, out_buf, stream.total_out - cnt, prog_name);
			cnt = stream.total_out;

			if (ret == Z_STREAM_END)
				goto done;
		}
	}

done:
	git_inflate_end(&stream);
	close(out);
	free(full_request);
}