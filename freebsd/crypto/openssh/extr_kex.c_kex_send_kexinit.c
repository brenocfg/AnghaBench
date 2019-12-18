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
typedef  int /*<<< orphan*/  u_char ;
struct ssh {struct kex* kex; } ;
struct kex {int flags; int /*<<< orphan*/  my; scalar_t__ done; } ;

/* Variables and functions */
 scalar_t__ KEX_COOKIE_LEN ; 
 int KEX_INIT_SENT ; 
 int /*<<< orphan*/  SSH2_MSG_KEXINIT ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int /*<<< orphan*/  arc4random_buf (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  debug (char*) ; 
 scalar_t__ sshbuf_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sshbuf_mutable_ptr (int /*<<< orphan*/ ) ; 
 int sshpkt_putb (struct ssh*,int /*<<< orphan*/ ) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 

int
kex_send_kexinit(struct ssh *ssh)
{
	u_char *cookie;
	struct kex *kex = ssh->kex;
	int r;

	if (kex == NULL)
		return SSH_ERR_INTERNAL_ERROR;
	if (kex->flags & KEX_INIT_SENT)
		return 0;
	kex->done = 0;

	/* generate a random cookie */
	if (sshbuf_len(kex->my) < KEX_COOKIE_LEN)
		return SSH_ERR_INVALID_FORMAT;
	if ((cookie = sshbuf_mutable_ptr(kex->my)) == NULL)
		return SSH_ERR_INTERNAL_ERROR;
	arc4random_buf(cookie, KEX_COOKIE_LEN);

	if ((r = sshpkt_start(ssh, SSH2_MSG_KEXINIT)) != 0 ||
	    (r = sshpkt_putb(ssh, kex->my)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		return r;
	debug("SSH2_MSG_KEXINIT sent");
	kex->flags |= KEX_INIT_SENT;
	return 0;
}