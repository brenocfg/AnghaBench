#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct bulk_checkin_state {scalar_t__ offset; int /*<<< orphan*/  f; scalar_t__ nr_written; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  obuf ;
typedef  int /*<<< orphan*/  ibuf ;
struct TYPE_7__ {unsigned char* next_out; int avail_out; unsigned char* next_in; scalar_t__ avail_in; } ;
typedef  TYPE_1__ git_zstream ;
typedef  int /*<<< orphan*/  git_hash_ctx ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_8__ {int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,unsigned char*,size_t) ;} ;

/* Variables and functions */
 unsigned int HASH_WRITE_OBJECT ; 
#define  Z_BUF_ERROR 130 
 int /*<<< orphan*/  Z_FINISH ; 
#define  Z_OK 129 
#define  Z_STREAM_END 128 
 int /*<<< orphan*/  die (char*,int,...) ; 
 int /*<<< orphan*/  die_errno (char*,char const*) ; 
 unsigned int encode_in_pack_object_header (unsigned char*,int,int,size_t) ; 
 int git_deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_deflate_abort (TYPE_1__*) ; 
 int /*<<< orphan*/  git_deflate_end (TYPE_1__*) ; 
 int /*<<< orphan*/  git_deflate_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashwrite (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  pack_compression_level ; 
 scalar_t__ pack_size_limit_cfg ; 
 scalar_t__ read_in_full (int,unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 TYPE_2__* the_hash_algo ; 

__attribute__((used)) static int stream_to_pack(struct bulk_checkin_state *state,
			  git_hash_ctx *ctx, off_t *already_hashed_to,
			  int fd, size_t size, enum object_type type,
			  const char *path, unsigned flags)
{
	git_zstream s;
	unsigned char obuf[16384];
	unsigned hdrlen;
	int status = Z_OK;
	int write_object = (flags & HASH_WRITE_OBJECT);
	off_t offset = 0;

	git_deflate_init(&s, pack_compression_level);

	hdrlen = encode_in_pack_object_header(obuf, sizeof(obuf), type, size);
	s.next_out = obuf + hdrlen;
	s.avail_out = sizeof(obuf) - hdrlen;

	while (status != Z_STREAM_END) {
		unsigned char ibuf[16384];

		if (size && !s.avail_in) {
			ssize_t rsize = size < sizeof(ibuf) ? size : sizeof(ibuf);
			ssize_t read_result = read_in_full(fd, ibuf, rsize);
			if (read_result < 0)
				die_errno("failed to read from '%s'", path);
			if (read_result != rsize)
				die("failed to read %d bytes from '%s'",
				    (int)rsize, path);
			offset += rsize;
			if (*already_hashed_to < offset) {
				size_t hsize = offset - *already_hashed_to;
				if (rsize < hsize)
					hsize = rsize;
				if (hsize)
					the_hash_algo->update_fn(ctx, ibuf, hsize);
				*already_hashed_to = offset;
			}
			s.next_in = ibuf;
			s.avail_in = rsize;
			size -= rsize;
		}

		status = git_deflate(&s, size ? 0 : Z_FINISH);

		if (!s.avail_out || status == Z_STREAM_END) {
			if (write_object) {
				size_t written = s.next_out - obuf;

				/* would we bust the size limit? */
				if (state->nr_written &&
				    pack_size_limit_cfg &&
				    pack_size_limit_cfg < state->offset + written) {
					git_deflate_abort(&s);
					return -1;
				}

				hashwrite(state->f, obuf, written);
				state->offset += written;
			}
			s.next_out = obuf;
			s.avail_out = sizeof(obuf);
		}

		switch (status) {
		case Z_OK:
		case Z_BUF_ERROR:
		case Z_STREAM_END:
			continue;
		default:
			die("unexpected deflate failure: %d", status);
		}
	}
	git_deflate_end(&s);
	return 0;
}