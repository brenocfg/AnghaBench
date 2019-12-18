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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int PACKET_READ_GENTLE_ON_EOF ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,size_t) ; 
 size_t read_in_full (int,void*,unsigned int) ; 

__attribute__((used)) static int get_packet_data(int fd, char **src_buf, size_t *src_size,
			   void *dst, unsigned size, int options)
{
	ssize_t ret;

	if (fd >= 0 && src_buf && *src_buf)
		BUG("multiple sources given to packet_read");

	/* Read up to "size" bytes from our source, whatever it is. */
	if (src_buf && *src_buf) {
		ret = size < *src_size ? size : *src_size;
		memcpy(dst, *src_buf, ret);
		*src_buf += ret;
		*src_size -= ret;
	} else {
		ret = read_in_full(fd, dst, size);
		if (ret < 0)
			die_errno(_("read error"));
	}

	/* And complain if we didn't get enough bytes to satisfy the read. */
	if (ret != size) {
		if (options & PACKET_READ_GENTLE_ON_EOF)
			return -1;

		die(_("the remote end hung up unexpectedly"));
	}

	return ret;
}