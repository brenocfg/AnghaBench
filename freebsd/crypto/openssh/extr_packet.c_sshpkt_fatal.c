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
struct ssh {TYPE_2__* state; TYPE_1__* kex; } ;
typedef  int /*<<< orphan*/  remote_id ;
struct TYPE_4__ {int /*<<< orphan*/  server_side; } ;
struct TYPE_3__ {int /*<<< orphan*/  failed_choice; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLACKLIST_AUTH_FAIL ; 
 int /*<<< orphan*/  BLACKLIST_NOTIFY (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ECONNRESET ; 
#define  SSH_ERR_CONN_CLOSED 136 
#define  SSH_ERR_CONN_TIMEOUT 135 
#define  SSH_ERR_DISCONNECTED 134 
#define  SSH_ERR_NO_CIPHER_ALG_MATCH 133 
#define  SSH_ERR_NO_COMPRESS_ALG_MATCH 132 
#define  SSH_ERR_NO_HOSTKEY_ALG_MATCH 131 
#define  SSH_ERR_NO_KEX_ALG_MATCH 130 
#define  SSH_ERR_NO_MAC_ALG_MATCH 129 
#define  SSH_ERR_SYSTEM_ERROR 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  logdie (char*,char const*,...) ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int /*<<< orphan*/  ssh_packet_clear_keys (struct ssh*) ; 
 int /*<<< orphan*/  sshpkt_fmt_connection_id (struct ssh*,char*,int) ; 

void
sshpkt_fatal(struct ssh *ssh, const char *tag, int r)
{
	char remote_id[512];

	sshpkt_fmt_connection_id(ssh, remote_id, sizeof(remote_id));

	switch (r) {
	case SSH_ERR_CONN_CLOSED:
		ssh_packet_clear_keys(ssh);
		logdie("Connection closed by %s", remote_id);
	case SSH_ERR_CONN_TIMEOUT:
		ssh_packet_clear_keys(ssh);
		logdie("Connection %s %s timed out",
		    ssh->state->server_side ? "from" : "to", remote_id);
	case SSH_ERR_DISCONNECTED:
		ssh_packet_clear_keys(ssh);
		logdie("Disconnected from %s", remote_id);
	case SSH_ERR_SYSTEM_ERROR:
		if (errno == ECONNRESET) {
			ssh_packet_clear_keys(ssh);
			logdie("Connection reset by %s", remote_id);
		}
		/* FALLTHROUGH */
	case SSH_ERR_NO_CIPHER_ALG_MATCH:
	case SSH_ERR_NO_MAC_ALG_MATCH:
	case SSH_ERR_NO_COMPRESS_ALG_MATCH:
	case SSH_ERR_NO_KEX_ALG_MATCH:
	case SSH_ERR_NO_HOSTKEY_ALG_MATCH:
		if (ssh && ssh->kex && ssh->kex->failed_choice) {
			BLACKLIST_NOTIFY(BLACKLIST_AUTH_FAIL, "ssh");
			ssh_packet_clear_keys(ssh);
			logdie("Unable to negotiate with %s: %s. "
			    "Their offer: %s", remote_id, ssh_err(r),
			    ssh->kex->failed_choice);
		}
		/* FALLTHROUGH */
	default:
		ssh_packet_clear_keys(ssh);
		logdie("%s%sConnection %s %s: %s",
		    tag != NULL ? tag : "", tag != NULL ? ": " : "",
		    ssh->state->server_side ? "from" : "to",
		    remote_id, ssh_err(r));
	}
}