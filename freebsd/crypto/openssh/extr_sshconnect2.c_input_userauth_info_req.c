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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  scalar_t__ u_int ;
typedef  scalar_t__ u_char ;
struct ssh {TYPE_1__* authctxt; } ;
struct TYPE_2__ {int info_req_seen; } ;
typedef  TYPE_1__ Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  RP_ECHO ; 
 int /*<<< orphan*/  SSH2_MSG_USERAUTH_INFO_RESPONSE ; 
 int /*<<< orphan*/  debug2 (char*,...) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freezero (char*,scalar_t__) ; 
 int /*<<< orphan*/  logit (char*,char*) ; 
 char* read_passphrase (char*,int /*<<< orphan*/ ) ; 
 int sshpkt_add_padding (struct ssh*,int) ; 
 int sshpkt_get_cstring (struct ssh*,char**,int /*<<< orphan*/ *) ; 
 int sshpkt_get_end (struct ssh*) ; 
 int sshpkt_get_u32 (struct ssh*,scalar_t__*) ; 
 int sshpkt_get_u8 (struct ssh*,scalar_t__*) ; 
 int sshpkt_put_cstring (struct ssh*,char*) ; 
 int sshpkt_put_u32 (struct ssh*,scalar_t__) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

int
input_userauth_info_req(int type, u_int32_t seq, struct ssh *ssh)
{
	Authctxt *authctxt = ssh->authctxt;
	char *name = NULL, *inst = NULL, *lang = NULL, *prompt = NULL;
	char *response = NULL;
	u_char echo = 0;
	u_int num_prompts, i;
	int r;

	debug2("input_userauth_info_req");

	if (authctxt == NULL)
		fatal("input_userauth_info_req: no authentication context");

	authctxt->info_req_seen = 1;

	if ((r = sshpkt_get_cstring(ssh, &name, NULL)) != 0 ||
	    (r = sshpkt_get_cstring(ssh, &inst, NULL)) != 0 ||
	    (r = sshpkt_get_cstring(ssh, &lang, NULL)) != 0)
		goto out;
	if (strlen(name) > 0)
		logit("%s", name);
	if (strlen(inst) > 0)
		logit("%s", inst);

	if ((r = sshpkt_get_u32(ssh, &num_prompts)) != 0)
		goto out;
	/*
	 * Begin to build info response packet based on prompts requested.
	 * We commit to providing the correct number of responses, so if
	 * further on we run into a problem that prevents this, we have to
	 * be sure and clean this up and send a correct error response.
	 */
	if ((r = sshpkt_start(ssh, SSH2_MSG_USERAUTH_INFO_RESPONSE)) != 0 ||
	    (r = sshpkt_put_u32(ssh, num_prompts)) != 0)
		goto out;

	debug2("input_userauth_info_req: num_prompts %d", num_prompts);
	for (i = 0; i < num_prompts; i++) {
		if ((r = sshpkt_get_cstring(ssh, &prompt, NULL)) != 0 ||
		    (r = sshpkt_get_u8(ssh, &echo)) != 0)
			goto out;
		response = read_passphrase(prompt, echo ? RP_ECHO : 0);
		if ((r = sshpkt_put_cstring(ssh, response)) != 0)
			goto out;
		freezero(response, strlen(response));
		free(prompt);
		response = prompt = NULL;
	}
	/* done with parsing incoming message. */
	if ((r = sshpkt_get_end(ssh)) != 0 ||
	    (r = sshpkt_add_padding(ssh, 64)) != 0)
		goto out;
	r = sshpkt_send(ssh);
 out:
	if (response)
		freezero(response, strlen(response));
	free(prompt);
	free(name);
	free(inst);
	free(lang);
	return r;
}