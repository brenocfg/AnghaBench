#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct channel_connect {int dummy; } ;
typedef  int /*<<< orphan*/  cctx ;
struct TYPE_4__ {struct channel_connect connect_ctx; int /*<<< orphan*/  type; int /*<<< orphan*/  host_port; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SSH_CHANNEL_RDYNAMIC_FINISH ; 
 int /*<<< orphan*/  channel_connect_ctx_free (struct channel_connect*) ; 
 int /*<<< orphan*/  channel_register_fds (struct ssh*,TYPE_1__*,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int connect_to_helper (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct channel_connect*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct channel_connect*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rdynamic_connect_finish(struct ssh *ssh, Channel *c)
{
	struct channel_connect cctx;
	int sock;

	memset(&cctx, 0, sizeof(cctx));
	sock = connect_to_helper(ssh, c->path, c->host_port, SOCK_STREAM, NULL,
	    NULL, &cctx, NULL, NULL);
	if (sock == -1)
		channel_connect_ctx_free(&cctx);
	else {
		/* similar to SSH_CHANNEL_CONNECTING but we've already sent the open */
		c->type = SSH_CHANNEL_RDYNAMIC_FINISH;
		c->connect_ctx = cctx;
		channel_register_fds(ssh, c, sock, sock, -1, 0, 1, 0);
	}
	return sock;
}