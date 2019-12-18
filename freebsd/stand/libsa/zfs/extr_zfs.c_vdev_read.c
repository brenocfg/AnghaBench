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
typedef  int /*<<< orphan*/  vdev_t ;
typedef  unsigned int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,unsigned int*) ; 
 int lseek (int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 unsigned int min (unsigned int,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 
 size_t read (int,char*,unsigned int) ; 
 size_t roundup2 (size_t,unsigned int) ; 
 char* zfs_alloc (unsigned int) ; 
 int /*<<< orphan*/  zfs_free (char*,unsigned int) ; 

__attribute__((used)) static int
vdev_read(vdev_t *vdev, void *priv, off_t offset, void *buf, size_t bytes)
{
	int fd, ret;
	size_t res, head, tail, total_size, full_sec_size;
	unsigned secsz, do_tail_read;
	off_t start_sec;
	char *outbuf, *bouncebuf;

	fd = (uintptr_t) priv;
	outbuf = (char *) buf;
	bouncebuf = NULL;

	ret = ioctl(fd, DIOCGSECTORSIZE, &secsz);
	if (ret != 0)
		return (ret);

	/*
	 * Handling reads of arbitrary offset and size - multi-sector case
	 * and single-sector case.
	 *
	 *                        Multi-sector Case
	 *                (do_tail_read = true if tail > 0)
	 *
	 *   |<----------------------total_size--------------------->|
	 *   |                                                       |
	 *   |<--head-->|<--------------bytes------------>|<--tail-->|
	 *   |          |                                 |          |
	 *   |          |       |<~full_sec_size~>|       |          |
	 *   +------------------+                 +------------------+
	 *   |          |0101010|     .  .  .     |0101011|          |
	 *   +------------------+                 +------------------+
	 *         start_sec                         start_sec + n
	 *
	 *
	 *                      Single-sector Case
	 *                    (do_tail_read = false)
	 *
	 *              |<------total_size = secsz----->|
	 *              |                               |
	 *              |<-head->|<---bytes--->|<-tail->|
	 *              +-------------------------------+
	 *              |        |0101010101010|        |
	 *              +-------------------------------+
	 *                          start_sec
	 */
	start_sec = offset / secsz;
	head = offset % secsz;
	total_size = roundup2(head + bytes, secsz);
	tail = total_size - (head + bytes);
	do_tail_read = ((tail > 0) && (head + bytes > secsz));
	full_sec_size = total_size;
	if (head > 0)
		full_sec_size -= secsz;
	if (do_tail_read)
		full_sec_size -= secsz;

	/* Return of partial sector data requires a bounce buffer. */
	if ((head > 0) || do_tail_read) {
		bouncebuf = zfs_alloc(secsz);
		if (bouncebuf == NULL) {
			printf("vdev_read: out of memory\n");
			return (ENOMEM);
		}
	}

	if (lseek(fd, start_sec * secsz, SEEK_SET) == -1) {
		ret = errno;
		goto error;
	}

	/* Partial data return from first sector */
	if (head > 0) {
		res = read(fd, bouncebuf, secsz);
		if (res != secsz) {
			ret = EIO;
			goto error;
		}
		memcpy(outbuf, bouncebuf + head, min(secsz - head, bytes));
		outbuf += min(secsz - head, bytes);
	}

	/* Full data return from read sectors */
	if (full_sec_size > 0) {
		res = read(fd, outbuf, full_sec_size);
		if (res != full_sec_size) {
			ret = EIO;
			goto error;
		}
		outbuf += full_sec_size;
	}

	/* Partial data return from last sector */
	if (do_tail_read) {
		res = read(fd, bouncebuf, secsz);
		if (res != secsz) {
			ret = EIO;
			goto error;
		}
		memcpy(outbuf, bouncebuf, secsz - tail);
	}

	ret = 0;
error:
	if (bouncebuf != NULL)
		zfs_free(bouncebuf, secsz);
	return (ret);
}