#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* fxstat; void* sendfile; void* dup2; void* fcntl; void* getsockopt; void* setsockopt; void* getsockname; void* getpeername; void* close; void* shutdown; void* poll; void* writev; void* write; void* sendmsg; void* sendto; void* send; void* readv; void* read; void* recvmsg; void* recvfrom; void* recv; void* connect; void* accept; void* listen; void* bind; void* socket; } ;
struct TYPE_3__ {void* fcntl; void* getsockopt; void* setsockopt; void* getsockname; void* getpeername; void* close; void* shutdown; void* poll; void* writev; void* write; void* sendmsg; void* sendto; void* send; void* readv; void* read; void* recvmsg; void* recvfrom; void* recv; void* connect; void* accept; void* listen; void* bind; void* socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTLD_DEFAULT ; 
 int /*<<< orphan*/  RTLD_NEXT ; 
 void* dlsym (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getenv_options () ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ real ; 
 TYPE_1__ rs ; 
 int /*<<< orphan*/  scan_config () ; 

__attribute__((used)) static void init_preload(void)
{
	static int init;

	/* Quick check without lock */
	if (init)
		return;

	pthread_mutex_lock(&mut);
	if (init)
		goto out;

	real.socket = dlsym(RTLD_NEXT, "socket");
	real.bind = dlsym(RTLD_NEXT, "bind");
	real.listen = dlsym(RTLD_NEXT, "listen");
	real.accept = dlsym(RTLD_NEXT, "accept");
	real.connect = dlsym(RTLD_NEXT, "connect");
	real.recv = dlsym(RTLD_NEXT, "recv");
	real.recvfrom = dlsym(RTLD_NEXT, "recvfrom");
	real.recvmsg = dlsym(RTLD_NEXT, "recvmsg");
	real.read = dlsym(RTLD_NEXT, "read");
	real.readv = dlsym(RTLD_NEXT, "readv");
	real.send = dlsym(RTLD_NEXT, "send");
	real.sendto = dlsym(RTLD_NEXT, "sendto");
	real.sendmsg = dlsym(RTLD_NEXT, "sendmsg");
	real.write = dlsym(RTLD_NEXT, "write");
	real.writev = dlsym(RTLD_NEXT, "writev");
	real.poll = dlsym(RTLD_NEXT, "poll");
	real.shutdown = dlsym(RTLD_NEXT, "shutdown");
	real.close = dlsym(RTLD_NEXT, "close");
	real.getpeername = dlsym(RTLD_NEXT, "getpeername");
	real.getsockname = dlsym(RTLD_NEXT, "getsockname");
	real.setsockopt = dlsym(RTLD_NEXT, "setsockopt");
	real.getsockopt = dlsym(RTLD_NEXT, "getsockopt");
	real.fcntl = dlsym(RTLD_NEXT, "fcntl");
	real.dup2 = dlsym(RTLD_NEXT, "dup2");
	real.sendfile = dlsym(RTLD_NEXT, "sendfile");
	real.fxstat = dlsym(RTLD_NEXT, "__fxstat");

	rs.socket = dlsym(RTLD_DEFAULT, "rsocket");
	rs.bind = dlsym(RTLD_DEFAULT, "rbind");
	rs.listen = dlsym(RTLD_DEFAULT, "rlisten");
	rs.accept = dlsym(RTLD_DEFAULT, "raccept");
	rs.connect = dlsym(RTLD_DEFAULT, "rconnect");
	rs.recv = dlsym(RTLD_DEFAULT, "rrecv");
	rs.recvfrom = dlsym(RTLD_DEFAULT, "rrecvfrom");
	rs.recvmsg = dlsym(RTLD_DEFAULT, "rrecvmsg");
	rs.read = dlsym(RTLD_DEFAULT, "rread");
	rs.readv = dlsym(RTLD_DEFAULT, "rreadv");
	rs.send = dlsym(RTLD_DEFAULT, "rsend");
	rs.sendto = dlsym(RTLD_DEFAULT, "rsendto");
	rs.sendmsg = dlsym(RTLD_DEFAULT, "rsendmsg");
	rs.write = dlsym(RTLD_DEFAULT, "rwrite");
	rs.writev = dlsym(RTLD_DEFAULT, "rwritev");
	rs.poll = dlsym(RTLD_DEFAULT, "rpoll");
	rs.shutdown = dlsym(RTLD_DEFAULT, "rshutdown");
	rs.close = dlsym(RTLD_DEFAULT, "rclose");
	rs.getpeername = dlsym(RTLD_DEFAULT, "rgetpeername");
	rs.getsockname = dlsym(RTLD_DEFAULT, "rgetsockname");
	rs.setsockopt = dlsym(RTLD_DEFAULT, "rsetsockopt");
	rs.getsockopt = dlsym(RTLD_DEFAULT, "rgetsockopt");
	rs.fcntl = dlsym(RTLD_DEFAULT, "rfcntl");

	getenv_options();
	scan_config();
	init = 1;
out:
	pthread_mutex_unlock(&mut);
}