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
struct ssh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_EXT_INFO ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int /*<<< orphan*/  free (char*) ; 
 char* sshkey_alg_list (int /*<<< orphan*/ ,int,int,char) ; 
 int sshpkt_put_cstring (struct ssh*,char*) ; 
 int sshpkt_put_u32 (struct ssh*,int) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kex_send_ext_info(struct ssh *ssh)
{
	int r;
	char *algs;

	if ((algs = sshkey_alg_list(0, 1, 1, ',')) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	/* XXX filter algs list by allowed pubkey/hostbased types */
	if ((r = sshpkt_start(ssh, SSH2_MSG_EXT_INFO)) != 0 ||
	    (r = sshpkt_put_u32(ssh, 1)) != 0 ||
	    (r = sshpkt_put_cstring(ssh, "server-sig-algs")) != 0 ||
	    (r = sshpkt_put_cstring(ssh, algs)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		goto out;
	/* success */
	r = 0;
 out:
	free(algs);
	return r;
}