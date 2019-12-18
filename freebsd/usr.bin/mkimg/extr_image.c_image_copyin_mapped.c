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
typedef  long uint64_t ;
typedef  long off_t ;
typedef  long lba_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_DATA ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_HOLE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int) ; 
 int errno ; 
 int image_chunk_copyin (long,char*,size_t,long,int) ; 
 int image_chunk_skipto (long) ; 
 int image_copyin_stream (long,int,long*) ; 
 void* image_file_map (int,long,size_t,long*) ; 
 int /*<<< orphan*/  image_file_unmap (void*,size_t) ; 
 long image_swap_pgsz ; 
 long lseek (int,long,int /*<<< orphan*/ ) ; 
 long secsz ; 

__attribute__((used)) static int
image_copyin_mapped(lba_t blk, int fd, uint64_t *sizep)
{
	off_t cur, data, end, hole, pos, iof;
	void *mp;
	char *buf;
	uint64_t bytesize;
	size_t iosz, sz;
	int error;

	/*
	 * We'd like to know the size of the file and we must
	 * be able to seek in order to mmap(2). If this isn't
	 * possible, then treat the file as a stream/pipe.
	 */
	end = lseek(fd, 0L, SEEK_END);
	if (end == -1L)
		return (image_copyin_stream(blk, fd, sizep));

	/*
	 * We need the file opened for the duration and our
	 * caller is going to close the file. Make a dup(2)
	 * so that control the faith of the descriptor.
	 */
	fd = dup(fd);
	if (fd == -1)
		return (errno);

	iosz = secsz * image_swap_pgsz;

	bytesize = 0;
	cur = pos = 0;
	error = 0;
	while (!error && cur < end) {
		hole = lseek(fd, cur, SEEK_HOLE);
		if (hole == -1)
			hole = end;
		data = lseek(fd, cur, SEEK_DATA);
		if (data == -1)
			data = end;

		/*
		 * Treat the entire file as data if sparse files
		 * are not supported by the underlying file system.
		 */
		if (hole == end && data == end)
			data = cur;

		if (cur == hole && data > hole) {
			hole = pos;
			pos = data & ~((uint64_t)secsz - 1);

			blk += (pos - hole) / secsz;
			error = image_chunk_skipto(blk);

			bytesize += pos - hole;
			cur = data;
		} else if (cur == data && hole > data) {
			data = pos;
			pos = (hole + secsz - 1) & ~((uint64_t)secsz - 1);

			while (data < pos) {
				sz = (pos - data > (off_t)iosz)
				    ? iosz : (size_t)(pos - data);

				buf = mp = image_file_map(fd, data, sz, &iof);
				if (mp != NULL) {
					buf += iof;
					error = image_chunk_copyin(blk, buf,
					    sz, data, fd);
					image_file_unmap(mp, sz);
				} else
					error = errno;

				blk += sz / secsz;
				bytesize += sz;
				data += sz;
			}
			cur = hole;
		} else {
			/*
			 * I don't know what this means or whether it
			 * can happen at all...
			 */
			assert(0);
		}
	}
	if (error)
		close(fd);
	if (!error && sizep != NULL)
		*sizep = bytesize;
	return (error);
}