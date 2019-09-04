#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ avail_in; scalar_t__ avail_out; int /*<<< orphan*/  next_out; void* next_in; } ;
typedef  TYPE_1__ z_stream ;
typedef  void* uInt ;
struct TYPE_6__ {size_t buf_size; int /*<<< orphan*/  digest; scalar_t__ compute_digest; int /*<<< orphan*/  last_error; int /*<<< orphan*/  z_buf; int /*<<< orphan*/  fd; int /*<<< orphan*/  flush_mode; TYPE_1__ zs; } ;
typedef  TYPE_2__ git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  BUFERR_WRITE ; 
 int /*<<< orphan*/  BUFERR_ZLIB ; 
 int /*<<< orphan*/  Z_FINISH ; 
 scalar_t__ Z_STREAM_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_hash_update (int /*<<< orphan*/ *,void*,size_t) ; 
 scalar_t__ p_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int write_deflate(git_filebuf *file, void *source, size_t len)
{
	z_stream *zs = &file->zs;

	if (len > 0 || file->flush_mode == Z_FINISH) {
		zs->next_in = source;
		zs->avail_in = (uInt)len;

		do {
			size_t have;

			zs->next_out = file->z_buf;
			zs->avail_out = (uInt)file->buf_size;

			if (deflate(zs, file->flush_mode) == Z_STREAM_ERROR) {
				file->last_error = BUFERR_ZLIB;
				return -1;
			}

			have = file->buf_size - (size_t)zs->avail_out;

			if (p_write(file->fd, file->z_buf, have) < 0) {
				file->last_error = BUFERR_WRITE;
				return -1;
			}

		} while (zs->avail_out == 0);

		assert(zs->avail_in == 0);

		if (file->compute_digest)
			git_hash_update(&file->digest, source, len);
	}

	return 0;
}