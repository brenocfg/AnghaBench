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
typedef  scalar_t__ u_char ;
struct ssh {int /*<<< orphan*/ * authctxt; } ;
typedef  int /*<<< orphan*/  Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pubkey_reset (int /*<<< orphan*/ *) ; 
 int sshpkt_get_cstring (struct ssh*,char**,int /*<<< orphan*/ *) ; 
 int sshpkt_get_end (struct ssh*) ; 
 int sshpkt_get_u8 (struct ssh*,scalar_t__*) ; 
 int /*<<< orphan*/  userauth (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  verbose (char*) ; 

int
input_userauth_failure(int type, u_int32_t seq, struct ssh *ssh)
{
	Authctxt *authctxt = ssh->authctxt;
	char *authlist = NULL;
	u_char partial;
	int r;

	if (authctxt == NULL)
		fatal("input_userauth_failure: no authentication context");

	if ((r = sshpkt_get_cstring(ssh, &authlist, NULL)) != 0 ||
	    (r = sshpkt_get_u8(ssh, &partial)) != 0 ||
	    (r = sshpkt_get_end(ssh)) != 0)
		goto out;

	if (partial != 0) {
		verbose("Authenticated with partial success.");
		/* reset state */
		pubkey_reset(authctxt);
	}
	debug("Authentications that can continue: %s", authlist);

	userauth(authctxt, authlist);
	authlist = NULL;
 out:
	free(authlist);
	return 0;
}