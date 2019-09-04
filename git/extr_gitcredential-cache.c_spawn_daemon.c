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
struct child_process {char const** argv; int no_stdin; int out; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (char*,int,char*) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int read_in_full (int,char*,int) ; 
 scalar_t__ start_command (struct child_process*) ; 

__attribute__((used)) static void spawn_daemon(const char *socket)
{
	struct child_process daemon = CHILD_PROCESS_INIT;
	const char *argv[] = { NULL, NULL, NULL };
	char buf[128];
	int r;

	argv[0] = "git-credential-cache--daemon";
	argv[1] = socket;
	daemon.argv = argv;
	daemon.no_stdin = 1;
	daemon.out = -1;

	if (start_command(&daemon))
		die_errno("unable to start cache daemon");
	r = read_in_full(daemon.out, buf, sizeof(buf));
	if (r < 0)
		die_errno("unable to read result code from cache daemon");
	if (r != 3 || memcmp(buf, "ok\n", 3))
		die("cache daemon did not start: %.*s", r, buf);
	close(daemon.out);
}