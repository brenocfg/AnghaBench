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
typedef  scalar_t__ uint16_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct sockaddr_storage {int dummy; } ;
struct module_env {int /*<<< orphan*/  scratch_buffer; int /*<<< orphan*/  outnet; int /*<<< orphan*/  rnd; int /*<<< orphan*/  worker_base; } ;
struct auth_xfer {TYPE_2__* task_transfer; int /*<<< orphan*/  name; } ;
struct auth_master {int /*<<< orphan*/  file; int /*<<< orphan*/  host; int /*<<< orphan*/  ssl; int /*<<< orphan*/  port; scalar_t__ http; scalar_t__ allow_notify; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  as ;
struct TYPE_4__ {scalar_t__ on_ixfr; scalar_t__ timer; int /*<<< orphan*/ * cp; scalar_t__ id; TYPE_1__* scan_addr; struct auth_master* master; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  addrlen; } ;

/* Variables and functions */
 int AUTH_TRANSFER_TIMEOUT ; 
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  addr_to_str (struct sockaddr_storage*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  auth_xfer_transfer_http_callback ; 
 int /*<<< orphan*/  auth_xfer_transfer_tcp_callback ; 
 int /*<<< orphan*/  auth_xfer_transfer_timer_callback ; 
 int /*<<< orphan*/  authextstrtoaddr (int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ *) ; 
 scalar_t__ comm_timer_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct auth_xfer*) ; 
 int /*<<< orphan*/  comm_timer_set (scalar_t__,struct timeval*) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  memmove (struct sockaddr_storage*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * outnet_comm_point_for_http (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct auth_xfer*,struct sockaddr_storage*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * outnet_comm_point_for_tcp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct auth_xfer*,struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sockaddr_store_port (struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 int ub_random (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*,char*,char*,...) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  xfr_create_ixfr_packet (struct auth_xfer*,int /*<<< orphan*/ ,scalar_t__,struct auth_master*) ; 

__attribute__((used)) static int
xfr_transfer_init_fetch(struct auth_xfer* xfr, struct module_env* env)
{
	struct sockaddr_storage addr;
	socklen_t addrlen = 0;
	struct auth_master* master = xfr->task_transfer->master;
	char *auth_name = NULL;
	struct timeval t;
	int timeout;
	if(!master) return 0;
	if(master->allow_notify) return 0; /* only for notify */

	/* get master addr */
	if(xfr->task_transfer->scan_addr) {
		addrlen = xfr->task_transfer->scan_addr->addrlen;
		memmove(&addr, &xfr->task_transfer->scan_addr->addr, addrlen);
	} else {
		if(!authextstrtoaddr(master->host, &addr, &addrlen, &auth_name)) {
			/* the ones that are not in addr format are supposed
			 * to be looked up.  The lookup has failed however,
			 * so skip them */
			char zname[255+1];
			dname_str(xfr->name, zname);
			log_err("%s: failed lookup, cannot transfer from master %s",
				zname, master->host);
			return 0;
		}
	}

	/* remove previous TCP connection (if any) */
	if(xfr->task_transfer->cp) {
		comm_point_delete(xfr->task_transfer->cp);
		xfr->task_transfer->cp = NULL;
	}
	if(!xfr->task_transfer->timer) {
		xfr->task_transfer->timer = comm_timer_create(env->worker_base,
			auth_xfer_transfer_timer_callback, xfr);
		if(!xfr->task_transfer->timer) {
			log_err("malloc failure");
			return 0;
		}
	}
	timeout = AUTH_TRANSFER_TIMEOUT;
#ifndef S_SPLINT_S
        t.tv_sec = timeout/1000;
        t.tv_usec = (timeout%1000)*1000;
#endif

	if(master->http) {
		/* perform http fetch */
		/* store http port number into sockaddr,
		 * unless someone used unbound's host@port notation */
		xfr->task_transfer->on_ixfr = 0;
		if(strchr(master->host, '@') == NULL)
			sockaddr_store_port(&addr, addrlen, master->port);
		xfr->task_transfer->cp = outnet_comm_point_for_http(
			env->outnet, auth_xfer_transfer_http_callback, xfr,
			&addr, addrlen, -1, master->ssl, master->host,
			master->file);
		if(!xfr->task_transfer->cp) {
			char zname[255+1], as[256];
			dname_str(xfr->name, zname);
			addr_to_str(&addr, addrlen, as, sizeof(as));
			verbose(VERB_ALGO, "cannot create http cp "
				"connection for %s to %s", zname, as);
			return 0;
		}
		comm_timer_set(xfr->task_transfer->timer, &t);
		if(verbosity >= VERB_ALGO) {
			char zname[255+1], as[256];
			dname_str(xfr->name, zname);
			addr_to_str(&addr, addrlen, as, sizeof(as));
			verbose(VERB_ALGO, "auth zone %s transfer next HTTP fetch from %s started", zname, as);
		}
		return 1;
	}

	/* perform AXFR/IXFR */
	/* set the packet to be written */
	/* create new ID */
	xfr->task_transfer->id = (uint16_t)(ub_random(env->rnd)&0xffff);
	xfr_create_ixfr_packet(xfr, env->scratch_buffer,
		xfr->task_transfer->id, master);

	/* connect on fd */
	xfr->task_transfer->cp = outnet_comm_point_for_tcp(env->outnet,
		auth_xfer_transfer_tcp_callback, xfr, &addr, addrlen,
		env->scratch_buffer, -1,
		auth_name != NULL, auth_name);
	if(!xfr->task_transfer->cp) {
		char zname[255+1], as[256];
 		dname_str(xfr->name, zname);
		addr_to_str(&addr, addrlen, as, sizeof(as));
		verbose(VERB_ALGO, "cannot create tcp cp connection for "
			"xfr %s to %s", zname, as);
		return 0;
	}
	comm_timer_set(xfr->task_transfer->timer, &t);
	if(verbosity >= VERB_ALGO) {
		char zname[255+1], as[256];
 		dname_str(xfr->name, zname);
		addr_to_str(&addr, addrlen, as, sizeof(as));
		verbose(VERB_ALGO, "auth zone %s transfer next %s fetch from %s started", zname, 
			(xfr->task_transfer->on_ixfr?"IXFR":"AXFR"), as);
	}
	return 1;
}