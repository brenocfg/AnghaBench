#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  void* u_int ;
struct ssh {int dummy; } ;
struct TYPE_6__ {scalar_t__ type; int remote_id; int have_remote_id; int self; int local_window; int local_maxpacket; void* remote_maxpacket; void* remote_window; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_CHANNEL_OPEN_CONFIRMATION ; 
 int /*<<< orphan*/  SSH2_MSG_CHANNEL_OPEN_FAILURE ; 
 int SSH2_OPEN_ADMINISTRATIVELY_PROHIBITED ; 
 scalar_t__ SSH_CHANNEL_CONNECTING ; 
 scalar_t__ SSH_CHANNEL_MUX_CLIENT ; 
 TYPE_1__* client_request_agent (struct ssh*,char*,int) ; 
 TYPE_1__* client_request_forwarded_streamlocal (struct ssh*,char*,int) ; 
 TYPE_1__* client_request_forwarded_tcpip (struct ssh*,char*,int,void*,void*) ; 
 TYPE_1__* client_request_x11 (struct ssh*,char*,int) ; 
 int /*<<< orphan*/  debug (char*,char*,...) ; 
 int /*<<< orphan*/  debug3 (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* packet_get_int () ; 
 char* packet_get_string (void**) ; 
 int /*<<< orphan*/  packet_put_cstring (char*) ; 
 int /*<<< orphan*/  packet_put_int (int) ; 
 int /*<<< orphan*/  packet_send () ; 
 int /*<<< orphan*/  packet_start (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
client_input_channel_open(int type, u_int32_t seq, struct ssh *ssh)
{
	Channel *c = NULL;
	char *ctype;
	int rchan;
	u_int rmaxpack, rwindow, len;

	ctype = packet_get_string(&len);
	rchan = packet_get_int();
	rwindow = packet_get_int();
	rmaxpack = packet_get_int();

	debug("client_input_channel_open: ctype %s rchan %d win %d max %d",
	    ctype, rchan, rwindow, rmaxpack);

	if (strcmp(ctype, "forwarded-tcpip") == 0) {
		c = client_request_forwarded_tcpip(ssh, ctype, rchan, rwindow,
		    rmaxpack);
	} else if (strcmp(ctype, "forwarded-streamlocal@openssh.com") == 0) {
		c = client_request_forwarded_streamlocal(ssh, ctype, rchan);
	} else if (strcmp(ctype, "x11") == 0) {
		c = client_request_x11(ssh, ctype, rchan);
	} else if (strcmp(ctype, "auth-agent@openssh.com") == 0) {
		c = client_request_agent(ssh, ctype, rchan);
	}
	if (c != NULL && c->type == SSH_CHANNEL_MUX_CLIENT) {
		debug3("proxied to downstream: %s", ctype);
	} else if (c != NULL) {
		debug("confirm %s", ctype);
		c->remote_id = rchan;
		c->have_remote_id = 1;
		c->remote_window = rwindow;
		c->remote_maxpacket = rmaxpack;
		if (c->type != SSH_CHANNEL_CONNECTING) {
			packet_start(SSH2_MSG_CHANNEL_OPEN_CONFIRMATION);
			packet_put_int(c->remote_id);
			packet_put_int(c->self);
			packet_put_int(c->local_window);
			packet_put_int(c->local_maxpacket);
			packet_send();
		}
	} else {
		debug("failure %s", ctype);
		packet_start(SSH2_MSG_CHANNEL_OPEN_FAILURE);
		packet_put_int(rchan);
		packet_put_int(SSH2_OPEN_ADMINISTRATIVELY_PROHIBITED);
		packet_put_cstring("open failed");
		packet_put_cstring("");
		packet_send();
	}
	free(ctype);
	return 0;
}