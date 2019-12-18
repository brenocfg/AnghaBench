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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int* u_int ;
typedef  int u_char ;
struct ssh {struct session_state* state; } ;
struct session_state {int /*<<< orphan*/  server_side; scalar_t__ keep_alive_timeouts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ) ; 
 int* SSH2_DISCONNECT_BY_APPLICATION ; 
#define  SSH2_MSG_DEBUG 131 
#define  SSH2_MSG_DISCONNECT 130 
#define  SSH2_MSG_IGNORE 129 
#define  SSH2_MSG_UNIMPLEMENTED 128 
 int SSH_ERR_DISCONNECTED ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_INFO ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  debug3 (char*) ; 
 int /*<<< orphan*/  do_log2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int ssh_packet_read_poll2 (struct ssh*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_port (struct ssh*) ; 
 int sshpkt_get_string (struct ssh*,int**,int /*<<< orphan*/ *) ; 
 int sshpkt_get_u32 (struct ssh*,int**) ; 
 int sshpkt_get_u8 (struct ssh*,int /*<<< orphan*/ *) ; 

int
ssh_packet_read_poll_seqnr(struct ssh *ssh, u_char *typep, u_int32_t *seqnr_p)
{
	struct session_state *state = ssh->state;
	u_int reason, seqnr;
	int r;
	u_char *msg;

	for (;;) {
		msg = NULL;
		r = ssh_packet_read_poll2(ssh, typep, seqnr_p);
		if (r != 0)
			return r;
		if (*typep) {
			state->keep_alive_timeouts = 0;
			DBG(debug("received packet type %d", *typep));
		}
		switch (*typep) {
		case SSH2_MSG_IGNORE:
			debug3("Received SSH2_MSG_IGNORE");
			break;
		case SSH2_MSG_DEBUG:
			if ((r = sshpkt_get_u8(ssh, NULL)) != 0 ||
			    (r = sshpkt_get_string(ssh, &msg, NULL)) != 0 ||
			    (r = sshpkt_get_string(ssh, NULL, NULL)) != 0) {
				free(msg);
				return r;
			}
			debug("Remote: %.900s", msg);
			free(msg);
			break;
		case SSH2_MSG_DISCONNECT:
			if ((r = sshpkt_get_u32(ssh, &reason)) != 0 ||
			    (r = sshpkt_get_string(ssh, &msg, NULL)) != 0)
				return r;
			/* Ignore normal client exit notifications */
			do_log2(ssh->state->server_side &&
			    reason == SSH2_DISCONNECT_BY_APPLICATION ?
			    SYSLOG_LEVEL_INFO : SYSLOG_LEVEL_ERROR,
			    "Received disconnect from %s port %d:"
			    "%u: %.400s", ssh_remote_ipaddr(ssh),
			    ssh_remote_port(ssh), reason, msg);
			free(msg);
			return SSH_ERR_DISCONNECTED;
		case SSH2_MSG_UNIMPLEMENTED:
			if ((r = sshpkt_get_u32(ssh, &seqnr)) != 0)
				return r;
			debug("Received SSH2_MSG_UNIMPLEMENTED for %u",
			    seqnr);
			break;
		default:
			return 0;
		}
	}
}