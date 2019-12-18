#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  self; int /*<<< orphan*/  local_maxpacket; int /*<<< orphan*/  local_window; } ;
typedef  TYPE_1__ Channel ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_CHANNEL_OPEN ; 
 int /*<<< orphan*/  fatal (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int sshpkt_put_cstring (struct ssh*,char const*) ; 
 int sshpkt_put_u32 (struct ssh*,int /*<<< orphan*/ ) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
open_preamble(struct ssh *ssh, const char *where, Channel *c, const char *type)
{
	int r;

	if ((r = sshpkt_start(ssh, SSH2_MSG_CHANNEL_OPEN)) != 0 ||
	    (r = sshpkt_put_cstring(ssh, type)) != 0 ||
	    (r = sshpkt_put_u32(ssh, c->self)) != 0 ||
	    (r = sshpkt_put_u32(ssh, c->local_window)) != 0 ||
	    (r = sshpkt_put_u32(ssh, c->local_maxpacket)) != 0) {
		fatal("%s: channel %i: open: %s", where, c->self, ssh_err(r));
	}
}