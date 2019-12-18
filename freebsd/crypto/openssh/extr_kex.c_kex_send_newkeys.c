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
struct ssh {TYPE_1__* kex; } ;
struct TYPE_2__ {scalar_t__ ext_info_c; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_NEWKEYS ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  kex_input_newkeys ; 
 int /*<<< orphan*/  kex_reset_dispatch (struct ssh*) ; 
 int kex_send_ext_info (struct ssh*) ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 

int
kex_send_newkeys(struct ssh *ssh)
{
	int r;

	kex_reset_dispatch(ssh);
	if ((r = sshpkt_start(ssh, SSH2_MSG_NEWKEYS)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		return r;
	debug("SSH2_MSG_NEWKEYS sent");
	debug("expecting SSH2_MSG_NEWKEYS");
	ssh_dispatch_set(ssh, SSH2_MSG_NEWKEYS, &kex_input_newkeys);
	if (ssh->kex->ext_info_c)
		if ((r = kex_send_ext_info(ssh)) != 0)
			return r;
	return 0;
}