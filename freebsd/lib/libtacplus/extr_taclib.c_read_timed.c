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
struct timeval {scalar_t__ tv_sec; } ;
struct tac_handle {scalar_t__ fd; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  generr (struct tac_handle*,char*,...) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int read (scalar_t__,char*,size_t) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  timersub (struct timeval const*,struct timeval*,struct timeval*) ; 

__attribute__((used)) static int
read_timed(struct tac_handle *h, void *buf, size_t len,
    const struct timeval *deadline)
{
	char *ptr;

	ptr = (char *)buf;
	while (len > 0) {
		int n;

		n = read(h->fd, ptr, len);
		if (n == -1) {
			struct timeval tv;
			int nfds;

			if (errno != EAGAIN) {
				generr(h, "Network read error: %s",
				    strerror(errno));
				return -1;
			}

			/* Wait until we can read more data. */
			gettimeofday(&tv, NULL);
			timersub(deadline, &tv, &tv);
			if (tv.tv_sec >= 0) {
				fd_set rfds;

				FD_ZERO(&rfds);
				FD_SET(h->fd, &rfds);
				nfds =
				    select(h->fd + 1, &rfds, NULL, NULL, &tv);
				if (nfds == -1) {
					generr(h, "select: %s",
					    strerror(errno));
					return -1;
				}
			} else
				nfds = 0;
			if (nfds == 0) {
				generr(h, "Network read timed out");
				return -1;
			}
		} else if (n == 0) {
			generr(h, "unexpected EOF from server");
			return -1;
		} else {
			ptr += n;
			len -= n;
		}
	}
	return 0;
}