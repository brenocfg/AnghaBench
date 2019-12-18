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
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH_AGENTC_LOCK ; 
 int /*<<< orphan*/  SSH_AGENTC_UNLOCK ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int decode_reply (int /*<<< orphan*/ ) ; 
 int ssh_request_reply (int,struct sshbuf*,struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int sshbuf_get_u8 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 struct sshbuf* sshbuf_new () ; 
 int sshbuf_put_cstring (struct sshbuf*,char const*) ; 
 int sshbuf_put_u8 (struct sshbuf*,int /*<<< orphan*/ ) ; 

int
ssh_lock_agent(int sock, int lock, const char *password)
{
	int r;
	u_char type = lock ? SSH_AGENTC_LOCK : SSH_AGENTC_UNLOCK;
	struct sshbuf *msg;

	if ((msg = sshbuf_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((r = sshbuf_put_u8(msg, type)) != 0 ||
	    (r = sshbuf_put_cstring(msg, password)) != 0)
		goto out;
	if ((r = ssh_request_reply(sock, msg, msg)) != 0)
		goto out;
	if ((r = sshbuf_get_u8(msg, &type)) != 0)
		goto out;
	r = decode_reply(type);
 out:
	sshbuf_free(msg);
	return r;
}