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
typedef  int timestamp_t ;
struct pollfd {int fd; int events; int revents; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int POLLIN ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int check_expirations () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int dup (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  serve_one_client (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning_errno (char*) ; 
 int /*<<< orphan*/ * xfdopen (int,char*) ; 

__attribute__((used)) static int serve_cache_loop(int fd)
{
	struct pollfd pfd;
	timestamp_t wakeup;

	wakeup = check_expirations();
	if (!wakeup)
		return 0;

	pfd.fd = fd;
	pfd.events = POLLIN;
	if (poll(&pfd, 1, 1000 * wakeup) < 0) {
		if (errno != EINTR)
			die_errno("poll failed");
		return 1;
	}

	if (pfd.revents & POLLIN) {
		int client, client2;
		FILE *in, *out;

		client = accept(fd, NULL, NULL);
		if (client < 0) {
			warning_errno("accept failed");
			return 1;
		}
		client2 = dup(client);
		if (client2 < 0) {
			warning_errno("dup failed");
			close(client);
			return 1;
		}

		in = xfdopen(client, "r");
		out = xfdopen(client2, "w");
		serve_one_client(in, out);
		fclose(in);
		fclose(out);
	}
	return 1;
}