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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die_errno (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ serve_cache_loop (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int unix_stream_listen (char const*) ; 

__attribute__((used)) static void serve_cache(const char *socket_path, int debug)
{
	int fd;

	fd = unix_stream_listen(socket_path);
	if (fd < 0)
		die_errno("unable to bind to '%s'", socket_path);

	printf("ok\n");
	fclose(stdout);
	if (!debug) {
		if (!freopen("/dev/null", "w", stderr))
			die_errno("unable to point stderr to /dev/null");
	}

	while (serve_cache_loop(fd))
		; /* nothing */

	close(fd);
}