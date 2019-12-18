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
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  remote_id ;
struct TYPE_2__ {scalar_t__ client_alive_count_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_GLOBAL_REQUEST ; 
 int channel_find_open (struct ssh*) ; 
 int /*<<< orphan*/  channel_request_start (struct ssh*,int,char*,int) ; 
 int /*<<< orphan*/  cleanup_exit (int) ; 
 int /*<<< orphan*/  logit (char*,char*) ; 
 TYPE_1__ options ; 
 scalar_t__ packet_inc_alive_timeouts () ; 
 int /*<<< orphan*/  packet_put_char (int) ; 
 int /*<<< orphan*/  packet_put_cstring (char*) ; 
 int /*<<< orphan*/  packet_send () ; 
 int /*<<< orphan*/  packet_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshpkt_fmt_connection_id (struct ssh*,char*,int) ; 

__attribute__((used)) static void
client_alive_check(struct ssh *ssh)
{
	int channel_id;
	char remote_id[512];

	/* timeout, check to see how many we have had */
	if (packet_inc_alive_timeouts() > options.client_alive_count_max) {
		sshpkt_fmt_connection_id(ssh, remote_id, sizeof(remote_id));
		logit("Timeout, client not responding from %s", remote_id);
		cleanup_exit(255);
	}

	/*
	 * send a bogus global/channel request with "wantreply",
	 * we should get back a failure
	 */
	if ((channel_id = channel_find_open(ssh)) == -1) {
		packet_start(SSH2_MSG_GLOBAL_REQUEST);
		packet_put_cstring("keepalive@openssh.com");
		packet_put_char(1);	/* boolean: want reply */
	} else {
		channel_request_start(ssh, channel_id,
		    "keepalive@openssh.com", 1);
	}
	packet_send();
}