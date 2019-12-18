#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct archive_write_disk {scalar_t__ filesize; scalar_t__ fd; int flags; size_t offset; scalar_t__ fd_offset; int /*<<< orphan*/  total_bytes_written; int /*<<< orphan*/  archive; TYPE_1__* pst; } ;
typedef  int ssize_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int st_blksize; } ;

/* Variables and functions */
 int ARCHIVE_EXTRACT_SPARSE ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int lazy_stat (struct archive_write_disk*) ; 
 scalar_t__ lseek (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int write (scalar_t__,char const*,int) ; 

__attribute__((used)) static ssize_t
write_data_block(struct archive_write_disk *a, const char *buff, size_t size)
{
	uint64_t start_size = size;
	ssize_t bytes_written = 0;
	ssize_t block_size = 0, bytes_to_write;

	if (size == 0)
		return (ARCHIVE_OK);

	if (a->filesize == 0 || a->fd < 0) {
		archive_set_error(&a->archive, 0,
		    "Attempt to write to an empty file");
		return (ARCHIVE_WARN);
	}

	if (a->flags & ARCHIVE_EXTRACT_SPARSE) {
#if HAVE_STRUCT_STAT_ST_BLKSIZE
		int r;
		if ((r = lazy_stat(a)) != ARCHIVE_OK)
			return (r);
		block_size = a->pst->st_blksize;
#else
		/* XXX TODO XXX Is there a more appropriate choice here ? */
		/* This needn't match the filesystem allocation size. */
		block_size = 16*1024;
#endif
	}

	/* If this write would run beyond the file size, truncate it. */
	if (a->filesize >= 0 && (int64_t)(a->offset + size) > a->filesize)
		start_size = size = (size_t)(a->filesize - a->offset);

	/* Write the data. */
	while (size > 0) {
		if (block_size == 0) {
			bytes_to_write = size;
		} else {
			/* We're sparsifying the file. */
			const char *p, *end;
			int64_t block_end;

			/* Skip leading zero bytes. */
			for (p = buff, end = buff + size; p < end; ++p) {
				if (*p != '\0')
					break;
			}
			a->offset += p - buff;
			size -= p - buff;
			buff = p;
			if (size == 0)
				break;

			/* Calculate next block boundary after offset. */
			block_end
			    = (a->offset / block_size + 1) * block_size;

			/* If the adjusted write would cross block boundary,
			 * truncate it to the block boundary. */
			bytes_to_write = size;
			if (a->offset + bytes_to_write > block_end)
				bytes_to_write = block_end - a->offset;
		}
		/* Seek if necessary to the specified offset. */
		if (a->offset != a->fd_offset) {
			if (lseek(a->fd, a->offset, SEEK_SET) < 0) {
				archive_set_error(&a->archive, errno,
				    "Seek failed");
				return (ARCHIVE_FATAL);
			}
			a->fd_offset = a->offset;
		}
		bytes_written = write(a->fd, buff, bytes_to_write);
		if (bytes_written < 0) {
			archive_set_error(&a->archive, errno, "Write failed");
			return (ARCHIVE_WARN);
		}
		buff += bytes_written;
		size -= bytes_written;
		a->total_bytes_written += bytes_written;
		a->offset += bytes_written;
		a->fd_offset = a->offset;
	}
	return (start_size - size);
}