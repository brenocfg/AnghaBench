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
struct ssh {struct kex* kex; } ;
struct kex {int /*<<< orphan*/  c25519_client_pubkey; int /*<<< orphan*/  c25519_client_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_KEX_ECDH_INIT ; 
 int /*<<< orphan*/  SSH2_MSG_KEX_ECDH_REPLY ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  dump_digest (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_kex_c25519_reply ; 
 int /*<<< orphan*/  kexc25519_keygen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sshpkt_put_string (struct ssh*,int /*<<< orphan*/ ,int) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 

int
kexc25519_client(struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	int r;

	kexc25519_keygen(kex->c25519_client_key, kex->c25519_client_pubkey);
#ifdef DEBUG_KEXECDH
	dump_digest("client private key:", kex->c25519_client_key,
	    sizeof(kex->c25519_client_key));
#endif
	if ((r = sshpkt_start(ssh, SSH2_MSG_KEX_ECDH_INIT)) != 0 ||
	    (r = sshpkt_put_string(ssh, kex->c25519_client_pubkey,
	    sizeof(kex->c25519_client_pubkey))) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		return r;

	debug("expecting SSH2_MSG_KEX_ECDH_REPLY");
	ssh_dispatch_set(ssh, SSH2_MSG_KEX_ECDH_REPLY, &input_kex_c25519_reply);
	return 0;
}