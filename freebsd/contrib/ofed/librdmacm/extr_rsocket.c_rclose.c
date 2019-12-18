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
struct rsocket {scalar_t__ type; int state; int opts; } ;

/* Variables and functions */
 int EBADF ; 
 int RS_OPT_SVC_ACTIVE ; 
 int /*<<< orphan*/  RS_SVC_REM_KEEPALIVE ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  ds_shutdown (struct rsocket*) ; 
 int /*<<< orphan*/  idm ; 
 struct rsocket* idm_lookup (int /*<<< orphan*/ *,int) ; 
 int rs_connected ; 
 int /*<<< orphan*/  rs_free (struct rsocket*) ; 
 int /*<<< orphan*/  rs_notify_svc (int /*<<< orphan*/ *,struct rsocket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rshutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_svc ; 

int rclose(int socket)
{
	struct rsocket *rs;

	rs = idm_lookup(&idm, socket);
	if (!rs)
		return EBADF;
	if (rs->type == SOCK_STREAM) {
		if (rs->state & rs_connected)
			rshutdown(socket, SHUT_RDWR);
		else if (rs->opts & RS_OPT_SVC_ACTIVE)
			rs_notify_svc(&tcp_svc, rs, RS_SVC_REM_KEEPALIVE);
	} else {
		ds_shutdown(rs);
	}

	rs_free(rs);
	return 0;
}