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
struct ssh {int /*<<< orphan*/ * authctxt; } ;
typedef  int /*<<< orphan*/  Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_EXT_INFO ; 
 int /*<<< orphan*/  SSH2_MSG_USERAUTH_BANNER ; 
 int /*<<< orphan*/  SSH2_MSG_USERAUTH_FAILURE ; 
 int /*<<< orphan*/  SSH2_MSG_USERAUTH_SUCCESS ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug2 (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_userauth_banner ; 
 int /*<<< orphan*/  input_userauth_error ; 
 int /*<<< orphan*/  input_userauth_failure ; 
 int /*<<< orphan*/  input_userauth_success ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ssh_packet_remaining (struct ssh*) ; 
 int sshpkt_get_cstring (struct ssh*,char**,int /*<<< orphan*/ *) ; 
 int sshpkt_get_end (struct ssh*) ; 
 int /*<<< orphan*/  userauth_none (int /*<<< orphan*/ *) ; 

int
input_userauth_service_accept(int type, u_int32_t seq, struct ssh *ssh)
{
	Authctxt *authctxt = ssh->authctxt;
	int r;

	if (ssh_packet_remaining(ssh) > 0) {
		char *reply;

		if ((r = sshpkt_get_cstring(ssh, &reply, NULL)) != 0)
			goto out;
		debug2("service_accept: %s", reply);
		free(reply);
	} else {
		debug2("buggy server: service_accept w/o service");
	}
	if ((r = sshpkt_get_end(ssh)) != 0)
		goto out;
	debug("SSH2_MSG_SERVICE_ACCEPT received");

	/* initial userauth request */
	userauth_none(authctxt);

	ssh_dispatch_set(ssh, SSH2_MSG_EXT_INFO, &input_userauth_error);
	ssh_dispatch_set(ssh, SSH2_MSG_USERAUTH_SUCCESS, &input_userauth_success);
	ssh_dispatch_set(ssh, SSH2_MSG_USERAUTH_FAILURE, &input_userauth_failure);
	ssh_dispatch_set(ssh, SSH2_MSG_USERAUTH_BANNER, &input_userauth_banner);
	r = 0;
 out:
	return r;
}