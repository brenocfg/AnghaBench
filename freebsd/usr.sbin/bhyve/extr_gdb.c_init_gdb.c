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
struct vmctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVF_READ ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 struct vmctx* ctx ; 
 int /*<<< orphan*/  debug (char*,int,char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errc (int,int,char*) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gdb_lock ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  idle_vcpus ; 
 int /*<<< orphan*/  limit_gdb_socket (int) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  mevent_add (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_connection ; 
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stepping_vcpu ; 
 int stopped_vcpu ; 
 int /*<<< orphan*/  vcpus_suspended ; 

void
init_gdb(struct vmctx *_ctx, int sport, bool wait)
{
	struct sockaddr_in sin;
	int error, flags, s;

	debug("==> starting on %d, %swaiting\n", sport, wait ? "" : "not ");

	error = pthread_mutex_init(&gdb_lock, NULL);
	if (error != 0)
		errc(1, error, "gdb mutex init");
	error = pthread_cond_init(&idle_vcpus, NULL);
	if (error != 0)
		errc(1, error, "gdb cv init");

	ctx = _ctx;
	s = socket(PF_INET, SOCK_STREAM, 0);
	if (s < 0)
		err(1, "gdb socket create");

	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(sport);

	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		err(1, "gdb socket bind");

	if (listen(s, 1) < 0)
		err(1, "gdb socket listen");

	if (wait) {
		/*
		 * Set vcpu 0 in vcpus_suspended.  This will trigger the
		 * logic in gdb_cpu_add() to suspend the first vcpu before
		 * it starts execution.  The vcpu will remain suspended
		 * until a debugger connects.
		 */
		stepping_vcpu = -1;
		stopped_vcpu = -1;
		CPU_SET(0, &vcpus_suspended);
	}

	flags = fcntl(s, F_GETFL);
	if (fcntl(s, F_SETFL, flags | O_NONBLOCK) == -1)
		err(1, "Failed to mark gdb socket non-blocking");

#ifndef WITHOUT_CAPSICUM
	limit_gdb_socket(s);
#endif
	mevent_add(s, EVF_READ, new_connection, NULL);
}