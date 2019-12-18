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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct child_process {int in; int /*<<< orphan*/  out; int /*<<< orphan*/  argv; int /*<<< orphan*/  env_array; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  add_child (struct child_process*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  check_dead_children () ; 
 TYPE_1__ cld_argv ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup (int) ; 
 int /*<<< orphan*/  inet_ntop (scalar_t__,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kill_some_child () ; 
 scalar_t__ live_children ; 
 int /*<<< orphan*/  logerror (char*) ; 
 scalar_t__ max_connections ; 
 char* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ start_command (struct child_process*) ; 

__attribute__((used)) static void handle(int incoming, struct sockaddr *addr, socklen_t addrlen)
{
	struct child_process cld = CHILD_PROCESS_INIT;

	if (max_connections && live_children >= max_connections) {
		kill_some_child();
		sleep(1);  /* give it some time to die */
		check_dead_children();
		if (live_children >= max_connections) {
			close(incoming);
			logerror("Too many children, dropping connection");
			return;
		}
	}

	if (addr->sa_family == AF_INET) {
		char buf[128] = "";
		struct sockaddr_in *sin_addr = (void *) addr;
		inet_ntop(addr->sa_family, &sin_addr->sin_addr, buf, sizeof(buf));
		argv_array_pushf(&cld.env_array, "REMOTE_ADDR=%s", buf);
		argv_array_pushf(&cld.env_array, "REMOTE_PORT=%d",
				 ntohs(sin_addr->sin_port));
#ifndef NO_IPV6
	} else if (addr->sa_family == AF_INET6) {
		char buf[128] = "";
		struct sockaddr_in6 *sin6_addr = (void *) addr;
		inet_ntop(AF_INET6, &sin6_addr->sin6_addr, buf, sizeof(buf));
		argv_array_pushf(&cld.env_array, "REMOTE_ADDR=[%s]", buf);
		argv_array_pushf(&cld.env_array, "REMOTE_PORT=%d",
				 ntohs(sin6_addr->sin6_port));
#endif
	}

	cld.argv = cld_argv.argv;
	cld.in = incoming;
	cld.out = dup(incoming);

	if (start_command(&cld))
		logerror("unable to fork");
	else
		add_child(&cld, addr, addrlen);
}