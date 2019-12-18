#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct ssh {TYPE_2__* authctxt; } ;
typedef  int /*<<< orphan*/  prompt ;
struct TYPE_6__ {char* host_key_alias; } ;
struct TYPE_5__ {char* host; char* server_user; char* service; TYPE_1__* method; } ;
struct TYPE_4__ {char* name; } ;
typedef  TYPE_2__ Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  RP_ALLOW_EOF ; 
 int /*<<< orphan*/  SSH2_MSG_USERAUTH_PASSWD_CHANGEREQ ; 
 int /*<<< orphan*/  SSH2_MSG_USERAUTH_REQUEST ; 
 int /*<<< orphan*/  debug2 (char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freezero (char*,scalar_t__) ; 
 int /*<<< orphan*/  logit (char*,...) ; 
 TYPE_3__ options ; 
 char* read_passphrase (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int (*) (int,int /*<<< orphan*/ ,struct ssh*)) ; 
 int sshpkt_add_padding (struct ssh*,int) ; 
 int sshpkt_get_cstring (struct ssh*,char**,int /*<<< orphan*/ *) ; 
 int sshpkt_put_cstring (struct ssh*,char*) ; 
 int sshpkt_put_u8 (struct ssh*,int) ; 
 int sshpkt_send (struct ssh*) ; 
 int sshpkt_start (struct ssh*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int
input_userauth_passwd_changereq(int type, u_int32_t seqnr, struct ssh *ssh)
{
	Authctxt *authctxt = ssh->authctxt;
	char *info = NULL, *lang = NULL, *password = NULL, *retype = NULL;
	char prompt[256];
	const char *host;
	int r;

	debug2("input_userauth_passwd_changereq");

	if (authctxt == NULL)
		fatal("input_userauth_passwd_changereq: "
		    "no authentication context");
	host = options.host_key_alias ? options.host_key_alias : authctxt->host;

	if ((r = sshpkt_get_cstring(ssh, &info, NULL)) != 0 ||
	    (r = sshpkt_get_cstring(ssh, &lang, NULL)) != 0)
		goto out;
	if (strlen(info) > 0)
		logit("%s", info);
	if ((r = sshpkt_start(ssh, SSH2_MSG_USERAUTH_REQUEST)) != 0 ||
	    (r = sshpkt_put_cstring(ssh, authctxt->server_user)) != 0 ||
	    (r = sshpkt_put_cstring(ssh, authctxt->service)) != 0 ||
	    (r = sshpkt_put_cstring(ssh, authctxt->method->name)) != 0 ||
	    (r = sshpkt_put_u8(ssh, 1)) != 0)	/* additional info */
		goto out;

	snprintf(prompt, sizeof(prompt),
	    "Enter %.30s@%.128s's old password: ",
	    authctxt->server_user, host);
	password = read_passphrase(prompt, 0);
	if ((r = sshpkt_put_cstring(ssh, password)) != 0)
		goto out;

	freezero(password, strlen(password));
	password = NULL;
	while (password == NULL) {
		snprintf(prompt, sizeof(prompt),
		    "Enter %.30s@%.128s's new password: ",
		    authctxt->server_user, host);
		password = read_passphrase(prompt, RP_ALLOW_EOF);
		if (password == NULL) {
			/* bail out */
			r = 0;
			goto out;
		}
		snprintf(prompt, sizeof(prompt),
		    "Retype %.30s@%.128s's new password: ",
		    authctxt->server_user, host);
		retype = read_passphrase(prompt, 0);
		if (strcmp(password, retype) != 0) {
			freezero(password, strlen(password));
			logit("Mismatch; try again, EOF to quit.");
			password = NULL;
		}
		freezero(retype, strlen(retype));
	}
	if ((r = sshpkt_put_cstring(ssh, password)) != 0 ||
	    (r = sshpkt_add_padding(ssh, 64)) != 0 ||
	    (r = sshpkt_send(ssh)) != 0)
		goto out;

	ssh_dispatch_set(ssh, SSH2_MSG_USERAUTH_PASSWD_CHANGEREQ,
	    &input_userauth_passwd_changereq);
	r = 0;
 out:
	if (password)
		freezero(password, strlen(password));
	free(info);
	free(lang);
	return r;
}