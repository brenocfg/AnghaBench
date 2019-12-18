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
struct sockaddr {int /*<<< orphan*/  sa_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,...) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* calloc (size_t,int) ; 
 int close (int) ; 
 int connect (int,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void
lb_simple_accept_loop(int domain, const struct sockaddr *addr, int sds[],
    size_t nsds, int nconns)
{
	size_t i;
	int *acceptcnt;
	int csd, error, excnt, sd;

	/*
	 * We expect each listening socket to accept roughly nconns/nsds
	 * connections, but allow for some error.
	 */
	excnt = nconns / nsds / 8;
	acceptcnt = calloc(nsds, sizeof(*acceptcnt));
	ATF_REQUIRE_MSG(acceptcnt != NULL, "calloc() failed: %s",
	    strerror(errno));

	while (nconns-- > 0) {
		sd = socket(domain, SOCK_STREAM, 0);
		ATF_REQUIRE_MSG(sd >= 0, "socket() failed: %s",
		    strerror(errno));

		error = connect(sd, addr, addr->sa_len);
		ATF_REQUIRE_MSG(error == 0, "connect() failed: %s",
		    strerror(errno));

		/*
		 * Poll the listening sockets.
		 */
		do {
			for (i = 0; i < nsds; i++) {
				csd = accept(sds[i], NULL, NULL);
				if (csd < 0) {
					ATF_REQUIRE_MSG(errno == EWOULDBLOCK ||
					    errno == EAGAIN,
					    "accept() failed: %s",
					    strerror(errno));
					continue;
				}

				error = close(csd);
				ATF_REQUIRE_MSG(error == 0,
				    "close() failed: %s", strerror(errno));

				acceptcnt[i]++;
				break;
			}
		} while (i == nsds);

		error = close(sd);
		ATF_REQUIRE_MSG(error == 0, "close() failed: %s",
		    strerror(errno));
	}

	for (i = 0; i < nsds; i++)
		ATF_REQUIRE_MSG(acceptcnt[i] > excnt, "uneven balancing");
}