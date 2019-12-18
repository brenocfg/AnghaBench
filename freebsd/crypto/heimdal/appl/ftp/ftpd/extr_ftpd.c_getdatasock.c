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
typedef  scalar_t__ uid_t ;
struct TYPE_2__ {scalar_t__ pw_uid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EADDRINUSE ; 
 int /*<<< orphan*/  IPTOS_THROUGHPUT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ctrl_addr ; 
 scalar_t__ data ; 
 int /*<<< orphan*/  data_source ; 
 int errno ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/ * fdopen (int,char const*) ; 
 TYPE_1__* pw ; 
 scalar_t__ seteuid (scalar_t__) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_get_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_get_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_address_and_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_set_reuseaddr (int,int) ; 
 int /*<<< orphan*/  socket_set_tos (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_sockaddr_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE *
getdatasock(const char *mode, int domain)
{
	int s, t, tries;

	if (data >= 0)
		return (fdopen(data, mode));
	if (seteuid(0) < 0)
		fatal("Failed to seteuid");
	s = socket(domain, SOCK_STREAM, 0);
	if (s < 0)
		goto bad;
	socket_set_reuseaddr (s, 1);
	/* anchor socket to avoid multi-homing problems */
	socket_set_address_and_port (data_source,
				     socket_get_address (ctrl_addr),
				     socket_get_port (data_source));

	for (tries = 1; ; tries++) {
		if (bind(s, data_source,
			 socket_sockaddr_size (data_source)) >= 0)
			break;
		if (errno != EADDRINUSE || tries > 10)
			goto bad;
		sleep(tries);
	}
	if (seteuid(pw->pw_uid) < 0)
		fatal("Failed to seteuid");
#ifdef IPTOS_THROUGHPUT
	socket_set_tos (s, IPTOS_THROUGHPUT);
#endif
	return (fdopen(s, mode));
bad:
	/* Return the real value of errno (close may change it) */
	t = errno;
	if (seteuid((uid_t)pw->pw_uid) < 0)
		fatal("Failed to seteuid");
	close(s);
	errno = t;
	return (NULL);
}