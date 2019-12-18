#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_5__ {scalar_t__ tun_open; } ;
struct TYPE_4__ {int datagram; int self; int local_window_max; int local_maxpacket; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_TCP_PACKET_DEFAULT ; 
 int /*<<< orphan*/  CHAN_TCP_WINDOW_DEFAULT ; 
 int /*<<< orphan*/  SSH2_MSG_CHANNEL_OPEN ; 
 int /*<<< orphan*/  SSH_CHANNEL_OPENING ; 
 int SSH_TUNMODE_NO ; 
 scalar_t__ SSH_TUNMODE_POINTOPOINT ; 
 TYPE_1__* channel_new (struct ssh*,char*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  channel_register_filter (struct ssh*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  error (char*) ; 
 TYPE_2__ options ; 
 int /*<<< orphan*/  packet_put_cstring (char*) ; 
 int /*<<< orphan*/  packet_put_int (int) ; 
 int /*<<< orphan*/  packet_send () ; 
 int /*<<< orphan*/  packet_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_tun_infilter ; 
 int /*<<< orphan*/  sys_tun_outfilter ; 
 int tun_open (int,int,char**) ; 

char *
client_request_tun_fwd(struct ssh *ssh, int tun_mode,
    int local_tun, int remote_tun)
{
	Channel *c;
	int fd;
	char *ifname = NULL;

	if (tun_mode == SSH_TUNMODE_NO)
		return 0;

	debug("Requesting tun unit %d in mode %d", local_tun, tun_mode);

	/* Open local tunnel device */
	if ((fd = tun_open(local_tun, tun_mode, &ifname)) == -1) {
		error("Tunnel device open failed.");
		return NULL;
	}
	debug("Tunnel forwarding using interface %s", ifname);

	c = channel_new(ssh, "tun", SSH_CHANNEL_OPENING, fd, fd, -1,
	    CHAN_TCP_WINDOW_DEFAULT, CHAN_TCP_PACKET_DEFAULT, 0, "tun", 1);
	c->datagram = 1;

#if defined(SSH_TUN_FILTER)
	if (options.tun_open == SSH_TUNMODE_POINTOPOINT)
		channel_register_filter(ssh, c->self, sys_tun_infilter,
		    sys_tun_outfilter, NULL, NULL);
#endif

	packet_start(SSH2_MSG_CHANNEL_OPEN);
	packet_put_cstring("tun@openssh.com");
	packet_put_int(c->self);
	packet_put_int(c->local_window_max);
	packet_put_int(c->local_maxpacket);
	packet_put_int(tun_mode);
	packet_put_int(remote_tun);
	packet_send();

	return ifname;
}