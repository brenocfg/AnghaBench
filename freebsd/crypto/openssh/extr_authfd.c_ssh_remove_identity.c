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
struct sshkey {scalar_t__ type; } ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ KEY_UNSPEC ; 
 int /*<<< orphan*/  SSH2_AGENTC_REMOVE_IDENTITY ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int decode_reply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int ssh_request_reply (int,struct sshbuf*,struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int sshbuf_get_u8 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 struct sshbuf* sshbuf_new () ; 
 int sshbuf_put_string (struct sshbuf*,int /*<<< orphan*/ *,size_t) ; 
 int sshbuf_put_u8 (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int sshkey_to_blob (struct sshkey*,int /*<<< orphan*/ **,size_t*) ; 

int
ssh_remove_identity(int sock, struct sshkey *key)
{
	struct sshbuf *msg;
	int r;
	u_char type, *blob = NULL;
	size_t blen;

	if ((msg = sshbuf_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;

	if (key->type != KEY_UNSPEC) {
		if ((r = sshkey_to_blob(key, &blob, &blen)) != 0)
			goto out;
		if ((r = sshbuf_put_u8(msg,
		    SSH2_AGENTC_REMOVE_IDENTITY)) != 0 ||
		    (r = sshbuf_put_string(msg, blob, blen)) != 0)
			goto out;
	} else {
		r = SSH_ERR_INVALID_ARGUMENT;
		goto out;
	}
	if ((r = ssh_request_reply(sock, msg, msg)) != 0)
		goto out;
	if ((r = sshbuf_get_u8(msg, &type)) != 0)
		goto out;
	r = decode_reply(type);
 out:
	if (blob != NULL) {
		explicit_bzero(blob, blen);
		free(blob);
	}
	sshbuf_free(msg);
	return r;
}