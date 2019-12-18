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

/* Variables and functions */
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
stream_server(int listenfd)
{
	int acceptfd;

	while (1) {
		acceptfd = accept(listenfd, NULL, NULL);
		if (acceptfd < 0) {
			warn("stream_server: accept");
			continue;
		}
		sleep(1);
		close(acceptfd);
	}
}