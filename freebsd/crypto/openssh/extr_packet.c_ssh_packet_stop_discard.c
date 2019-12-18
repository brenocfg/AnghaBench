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
struct ssh {struct session_state* state; } ;
struct TYPE_2__ {int /*<<< orphan*/  seqnr; } ;
struct session_state {size_t packet_discard_mac_already; int /*<<< orphan*/  incoming_packet; TYPE_1__ p_read; scalar_t__ packet_discard_mac; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 size_t PACKET_MAX_SIZE ; 
 int SSH_ERR_MAC_INVALID ; 
 int /*<<< orphan*/  logit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_compute (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_port (struct ssh*) ; 
 size_t sshbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_ptr (int /*<<< orphan*/ ) ; 
 int sshbuf_put (int /*<<< orphan*/ ,char*,int) ; 

int
ssh_packet_stop_discard(struct ssh *ssh)
{
	struct session_state *state = ssh->state;
	int r;

	if (state->packet_discard_mac) {
		char buf[1024];
		size_t dlen = PACKET_MAX_SIZE;

		if (dlen > state->packet_discard_mac_already)
			dlen -= state->packet_discard_mac_already;
		memset(buf, 'a', sizeof(buf));
		while (sshbuf_len(state->incoming_packet) < dlen)
			if ((r = sshbuf_put(state->incoming_packet, buf,
			    sizeof(buf))) != 0)
				return r;
		(void) mac_compute(state->packet_discard_mac,
		    state->p_read.seqnr,
		    sshbuf_ptr(state->incoming_packet), dlen,
		    NULL, 0);
	}
	logit("Finished discarding for %.200s port %d",
	    ssh_remote_ipaddr(ssh), ssh_remote_port(ssh));
	return SSH_ERR_MAC_INVALID;
}