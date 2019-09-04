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
struct hashfile {scalar_t__ check_fd; int total; int /*<<< orphan*/  name; int /*<<< orphan*/  tp; int /*<<< orphan*/  fd; } ;
typedef  unsigned int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_throughput (int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (void const*,unsigned char*,unsigned int) ; 
 unsigned int read_in_full (scalar_t__,unsigned char*,unsigned int) ; 
 int xwrite (int /*<<< orphan*/ ,void const*,unsigned int) ; 

__attribute__((used)) static void flush(struct hashfile *f, const void *buf, unsigned int count)
{
	if (0 <= f->check_fd && count)  {
		unsigned char check_buffer[8192];
		ssize_t ret = read_in_full(f->check_fd, check_buffer, count);

		if (ret < 0)
			die_errno("%s: sha1 file read error", f->name);
		if (ret != count)
			die("%s: sha1 file truncated", f->name);
		if (memcmp(buf, check_buffer, count))
			die("sha1 file '%s' validation error", f->name);
	}

	for (;;) {
		int ret = xwrite(f->fd, buf, count);
		if (ret > 0) {
			f->total += ret;
			display_throughput(f->tp, f->total);
			buf = (char *) buf + ret;
			count -= ret;
			if (count)
				continue;
			return;
		}
		if (!ret)
			die("sha1 file '%s' write error. Out of diskspace", f->name);
		die_errno("sha1 file '%s' write error", f->name);
	}
}