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
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SSH_RANDOM_DEV ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getrandom (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void
getrnd(u_char *s, size_t len)
{
	int fd;
	ssize_t r;
	size_t o = 0;

#ifdef HAVE_GETRANDOM
	if ((r = getrandom(s, len, 0)) > 0 && (size_t)r == len)
		return;
#endif /* HAVE_GETRANDOM */

	if ((fd = open(SSH_RANDOM_DEV, O_RDONLY)) == -1)
		fatal("Couldn't open %s: %s", SSH_RANDOM_DEV, strerror(errno));
	while (o < len) {
		r = read(fd, s + o, len - o);
		if (r < 0) {
			if (errno == EAGAIN || errno == EINTR ||
			    errno == EWOULDBLOCK)
				continue;
			fatal("read %s: %s", SSH_RANDOM_DEV, strerror(errno));
		}
		o += r;
	}
	close(fd);
}