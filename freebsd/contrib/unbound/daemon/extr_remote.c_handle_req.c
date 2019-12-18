#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rc_state {TYPE_1__* c; } ;
struct daemon_remote {int /*<<< orphan*/  worker; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  pre ;
typedef  int /*<<< orphan*/  magic ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int /*<<< orphan*/  fd; scalar_t__ ssl; } ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ RES ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ SSL_ERROR_ZERO_RETURN ; 
 scalar_t__ SSL_get_error (scalar_t__,int) ; 
 int SSL_read (scalar_t__,char*,int) ; 
 int UNBOUND_CONTROL_VERSION ; 
 int /*<<< orphan*/  VERB_DETAIL ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  WSAEventSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execute_cmd (struct daemon_remote*,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_set_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  ssl_printf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ssl_read_line (TYPE_2__*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wsa_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_req(struct daemon_remote* rc, struct rc_state* s, RES* res)
{
	int r;
	char pre[10];
	char magic[7];
	char buf[1024];
#ifdef USE_WINSOCK
	/* makes it possible to set the socket blocking again. */
	/* basically removes it from winsock_event ... */
	WSAEventSelect(s->c->fd, NULL, 0);
#endif
	fd_set_block(s->c->fd);

	/* try to read magic UBCT[version]_space_ string */
	if(res->ssl) {
		ERR_clear_error();
		if((r=SSL_read(res->ssl, magic, (int)sizeof(magic)-1)) <= 0) {
			if(SSL_get_error(res->ssl, r) == SSL_ERROR_ZERO_RETURN)
				return;
			log_crypto_err("could not SSL_read");
			return;
		}
	} else {
		while(1) {
			ssize_t rr = recv(res->fd, magic, sizeof(magic)-1, 0);
			if(rr <= 0) {
				if(rr == 0) return;
				if(errno == EINTR || errno == EAGAIN)
					continue;
#ifndef USE_WINSOCK
				log_err("could not recv: %s", strerror(errno));
#else
				log_err("could not recv: %s", wsa_strerror(WSAGetLastError()));
#endif
				return;
			}
			r = (int)rr;
			break;
		}
	}
	magic[6] = 0;
	if( r != 6 || strncmp(magic, "UBCT", 4) != 0) {
		verbose(VERB_QUERY, "control connection has bad magic string");
		/* probably wrong tool connected, ignore it completely */
		return;
	}

	/* read the command line */
	if(!ssl_read_line(res, buf, sizeof(buf))) {
		return;
	}
	snprintf(pre, sizeof(pre), "UBCT%d ", UNBOUND_CONTROL_VERSION);
	if(strcmp(magic, pre) != 0) {
		verbose(VERB_QUERY, "control connection had bad "
			"version %s, cmd: %s", magic, buf);
		ssl_printf(res, "error version mismatch\n");
		return;
	}
	verbose(VERB_DETAIL, "control cmd: %s", buf);

	/* figure out what to do */
	execute_cmd(rc, res, buf, rc->worker);
}