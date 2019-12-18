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
struct TYPE_4__ {int host_port; struct channel_connect connect_ctx; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_TCP_PACKET_DEFAULT ; 
 int /*<<< orphan*/  CHAN_TCP_WINDOW_DEFAULT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SSH_CHANNEL_CONNECTING ; 
 int /*<<< orphan*/  channel_connect_ctx_free (struct channel_connect*) ; 
 TYPE_1__* channel_new (struct ssh*,char*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int connect_to_helper (struct ssh*,char const*,int,int /*<<< orphan*/ ,char*,char*,struct channel_connect*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct channel_connect*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static Channel *
connect_to(struct ssh *ssh, const char *host, int port,
    char *ctype, char *rname)
{
	struct channel_connect cctx;
	Channel *c;
	int sock;

	memset(&cctx, 0, sizeof(cctx));
	sock = connect_to_helper(ssh, host, port, SOCK_STREAM, ctype, rname,
	    &cctx, NULL, NULL);
	if (sock == -1) {
		channel_connect_ctx_free(&cctx);
		return NULL;
	}
	c = channel_new(ssh, ctype, SSH_CHANNEL_CONNECTING, sock, sock, -1,
	    CHAN_TCP_WINDOW_DEFAULT, CHAN_TCP_PACKET_DEFAULT, 0, rname, 1);
	c->host_port = port;
	c->path = xstrdup(host);
	c->connect_ctx = cctx;

	return c;
}