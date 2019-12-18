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
struct pollfd {int fd; int events; int revents; } ;
struct addrinfo {int ai_socktype; struct addrinfo* ai_next; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_family; } ;
typedef  size_t nfds_t ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int INFTIM ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int SOCK_NONBLOCK ; 
 struct pollfd* calloc (size_t,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (struct pollfd*) ; 
 int poll (struct pollfd*,size_t,int) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
connect_to_any_host(struct addrinfo *hostres)
{
	struct addrinfo *res;
	nfds_t i, j;
	size_t count;
	struct pollfd *fds;
	int timeout = 180, s = -1;

	for (res = hostres, count = 0; res; res = res->ai_next)
		count++;
	fds = calloc(count, sizeof(*fds));
	if (fds == NULL)
		err(EX_OSERR, "calloc()");

	/*
	 * Traverse the result list elements and make non-block
	 * connection attempts.
	 */
	count = i = 0;
	for (res = hostres; res != NULL; res = res->ai_next) {
		s = socket(res->ai_family, res->ai_socktype | SOCK_NONBLOCK,
		    res->ai_protocol);
		if (s < 0)
			continue;
		if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
			if (errno == EINPROGRESS) {
				/* Add the socket to poll list */
				fds[i].fd = s;
				fds[i].events = POLLERR | POLLHUP |
						POLLIN | POLLOUT;
				/*
				 * From here until a socket connects, the
				 * socket fd is owned by the fds[] poll array.
				 */
				s = -1;
				count++;
				i++;
			} else {
				close(s);
				s = -1;

				/*
				 * Poll only if we have something to poll,
				 * otherwise just go ahead and try next
				 * address
				 */
				if (count == 0)
					continue;
			}
		} else
			goto done;

		/*
		 * If we are at the last address, poll until a connection is
		 * established or we failed all connection attempts.
		 */
		if (res->ai_next == NULL)
			timeout = INFTIM;

		/*
		 * Poll the watched descriptors for successful connections:
		 * if we still have more untried resolved addresses, poll only
		 * once; otherwise, poll until all descriptors have errors,
		 * which will be considered as ETIMEDOUT later.
		 */
		do {
			int n;

			n = poll(fds, i, timeout);
			if (n == 0) {
				/*
				 * No event reported in time.  Try with a
				 * smaller timeout (but cap at 2-3ms)
				 * after a new host have been added.
				 */
				if (timeout >= 3)
					timeout >>= 1;

				break;
			} else if (n < 0) {
				/*
				 * errno here can only be EINTR which we would
				 * want to clean up and bail out.
				 */
				s = -1;
				goto done;
			}

			/*
			 * Check for the event(s) we have seen.
			 */
			for (j = 0; j < i; j++) {
				if (fds[j].fd == -1 || fds[j].events == 0 ||
				    fds[j].revents == 0)
					continue;
				if (fds[j].revents & ~(POLLIN | POLLOUT)) {
					close(fds[j].fd);
					fds[j].fd = -1;
					fds[j].events = 0;
					count--;
					continue;
				} else if (fds[j].revents & (POLLIN | POLLOUT)) {
					/* Connect succeeded. */
					s = fds[j].fd;
					fds[j].fd = -1;

					goto done;
				}

			}
		} while (timeout == INFTIM && count != 0);
	}

	/* All attempts were failed */
	s = -1;
	if (count == 0)
		errno = ETIMEDOUT;

done:
	/* Close all watched fds except the succeeded one */
	for (j = 0; j < i; j++)
		if (fds[j].fd != -1)
			close(fds[j].fd);
	free(fds);
	return (s);
}