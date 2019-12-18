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
struct ssh {struct kex* kex; } ;
struct kex {int done; int /*<<< orphan*/ * name; int /*<<< orphan*/  flags; int /*<<< orphan*/  peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEX_INIT_SENT ; 
 int /*<<< orphan*/  MODE_IN ; 
 int /*<<< orphan*/  SSH2_MSG_KEXINIT ; 
 int /*<<< orphan*/  SSH2_MSG_NEWKEYS ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kex_input_kexinit ; 
 int /*<<< orphan*/  kex_protocol_error ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ssh_set_newkeys (struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_reset (int /*<<< orphan*/ ) ; 
 int sshpkt_get_end (struct ssh*) ; 

__attribute__((used)) static int
kex_input_newkeys(int type, u_int32_t seq, struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	int r;

	debug("SSH2_MSG_NEWKEYS received");
	ssh_dispatch_set(ssh, SSH2_MSG_NEWKEYS, &kex_protocol_error);
	ssh_dispatch_set(ssh, SSH2_MSG_KEXINIT, &kex_input_kexinit);
	if ((r = sshpkt_get_end(ssh)) != 0)
		return r;
	if ((r = ssh_set_newkeys(ssh, MODE_IN)) != 0)
		return r;
	kex->done = 1;
	sshbuf_reset(kex->peer);
	/* sshbuf_reset(kex->my); */
	kex->flags &= ~KEX_INIT_SENT;
	free(kex->name);
	kex->name = NULL;
	return 0;
}