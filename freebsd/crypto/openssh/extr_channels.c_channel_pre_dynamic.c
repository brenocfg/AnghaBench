#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_7__ {int /*<<< orphan*/  type; int /*<<< orphan*/  sock; int /*<<< orphan*/  output; int /*<<< orphan*/  self; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSH_CHANNEL_OPENING ; 
 int /*<<< orphan*/  chan_mark_dead (struct ssh*,TYPE_1__*) ; 
 int channel_decode_socks4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int channel_decode_socks5 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug2 (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  port_open_helper (struct ssh*,TYPE_1__*,char*) ; 
 int sshbuf_len (int /*<<< orphan*/ ) ; 
 int* sshbuf_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
channel_pre_dynamic(struct ssh *ssh, Channel *c,
    fd_set *readset, fd_set *writeset)
{
	const u_char *p;
	u_int have;
	int ret;

	have = sshbuf_len(c->input);
	debug2("channel %d: pre_dynamic: have %d", c->self, have);
	/* sshbuf_dump(c->input, stderr); */
	/* check if the fixed size part of the packet is in buffer. */
	if (have < 3) {
		/* need more */
		FD_SET(c->sock, readset);
		return;
	}
	/* try to guess the protocol */
	p = sshbuf_ptr(c->input);
	/* XXX sshbuf_peek_u8? */
	switch (p[0]) {
	case 0x04:
		ret = channel_decode_socks4(c, c->input, c->output);
		break;
	case 0x05:
		ret = channel_decode_socks5(c, c->input, c->output);
		break;
	default:
		ret = -1;
		break;
	}
	if (ret < 0) {
		chan_mark_dead(ssh, c);
	} else if (ret == 0) {
		debug2("channel %d: pre_dynamic: need more", c->self);
		/* need more */
		FD_SET(c->sock, readset);
		if (sshbuf_len(c->output))
			FD_SET(c->sock, writeset);
	} else {
		/* switch to the next state */
		c->type = SSH_CHANNEL_OPENING;
		port_open_helper(ssh, c, "direct-tcpip");
	}
}