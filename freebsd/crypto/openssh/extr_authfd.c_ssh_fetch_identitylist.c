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
typedef  size_t u_int32_t ;
typedef  scalar_t__ u_char ;
struct sshbuf {int dummy; } ;
struct ssh_identitylist {size_t nkeys; int /*<<< orphan*/ * comments; int /*<<< orphan*/ * keys; } ;

/* Variables and functions */
 size_t MAX_AGENT_IDENTITIES ; 
 int /*<<< orphan*/  SSH2_AGENTC_REQUEST_IDENTITIES ; 
 scalar_t__ SSH2_AGENT_IDENTITIES_ANSWER ; 
 int SSH_ERR_AGENT_FAILURE ; 
 int SSH_ERR_AGENT_NO_IDENTITIES ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_KEY_TYPE_UNKNOWN ; 
 scalar_t__ agent_failed (scalar_t__) ; 
 void* calloc (size_t,int) ; 
 int deserialise_identity2 (struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssh_free_identitylist (struct ssh_identitylist*) ; 
 int ssh_request_reply (int,struct sshbuf*,struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 int sshbuf_get_u32 (struct sshbuf*,size_t*) ; 
 int sshbuf_get_u8 (struct sshbuf*,scalar_t__*) ; 
 struct sshbuf* sshbuf_new () ; 
 int sshbuf_put_u8 (struct sshbuf*,int /*<<< orphan*/ ) ; 

int
ssh_fetch_identitylist(int sock, struct ssh_identitylist **idlp)
{
	u_char type;
	u_int32_t num, i;
	struct sshbuf *msg;
	struct ssh_identitylist *idl = NULL;
	int r;

	/*
	 * Send a message to the agent requesting for a list of the
	 * identities it can represent.
	 */
	if ((msg = sshbuf_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((r = sshbuf_put_u8(msg, SSH2_AGENTC_REQUEST_IDENTITIES)) != 0)
		goto out;

	if ((r = ssh_request_reply(sock, msg, msg)) != 0)
		goto out;

	/* Get message type, and verify that we got a proper answer. */
	if ((r = sshbuf_get_u8(msg, &type)) != 0)
		goto out;
	if (agent_failed(type)) {
		r = SSH_ERR_AGENT_FAILURE;
		goto out;
	} else if (type != SSH2_AGENT_IDENTITIES_ANSWER) {
		r = SSH_ERR_INVALID_FORMAT;
		goto out;
	}

	/* Get the number of entries in the response and check it for sanity. */
	if ((r = sshbuf_get_u32(msg, &num)) != 0)
		goto out;
	if (num > MAX_AGENT_IDENTITIES) {
		r = SSH_ERR_INVALID_FORMAT;
		goto out;
	}
	if (num == 0) {
		r = SSH_ERR_AGENT_NO_IDENTITIES;
		goto out;
	}

	/* Deserialise the response into a list of keys/comments */
	if ((idl = calloc(1, sizeof(*idl))) == NULL ||
	    (idl->keys = calloc(num, sizeof(*idl->keys))) == NULL ||
	    (idl->comments = calloc(num, sizeof(*idl->comments))) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	for (i = 0; i < num;) {
		if ((r = deserialise_identity2(msg, &(idl->keys[i]),
		    &(idl->comments[i]))) != 0) {
			if (r == SSH_ERR_KEY_TYPE_UNKNOWN) {
				/* Gracefully skip unknown key types */
				num--;
				continue;
			} else
				goto out;
		}
		i++;
	}
	idl->nkeys = num;
	*idlp = idl;
	idl = NULL;
	r = 0;
 out:
	sshbuf_free(msg);
	if (idl != NULL)
		ssh_free_identitylist(idl);
	return r;
}