#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_8__ {char* methoddata; char* authlist; TYPE_1__* method; int /*<<< orphan*/  host; int /*<<< orphan*/  server_user; } ;
struct TYPE_7__ {scalar_t__ (* userauth ) (TYPE_2__*) ;int /*<<< orphan*/ * enabled; int /*<<< orphan*/  name; int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;} ;
typedef  TYPE_1__ Authmethod ;
typedef  TYPE_2__ Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_USERAUTH_PER_METHOD_MAX ; 
 int /*<<< orphan*/  SSH2_MSG_USERAUTH_PER_METHOD_MIN ; 
 struct ssh* active_state ; 
 TYPE_1__* authmethod_get (char*) ; 
 int /*<<< orphan*/  debug2 (char*,...) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ssh_dispatch_range (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ stub2 (TYPE_2__*) ; 

void
userauth(Authctxt *authctxt, char *authlist)
{
	struct ssh *ssh = active_state; /* XXX */

	if (authctxt->method != NULL && authctxt->method->cleanup != NULL)
		authctxt->method->cleanup(authctxt);

	free(authctxt->methoddata);
	authctxt->methoddata = NULL;
	if (authlist == NULL) {
		authlist = authctxt->authlist;
	} else {
		free(authctxt->authlist);
		authctxt->authlist = authlist;
	}
	for (;;) {
		Authmethod *method = authmethod_get(authlist);
		if (method == NULL)
			fatal("%s@%s: Permission denied (%s).",
			    authctxt->server_user, authctxt->host, authlist);
		authctxt->method = method;

		/* reset the per method handler */
		ssh_dispatch_range(ssh, SSH2_MSG_USERAUTH_PER_METHOD_MIN,
		    SSH2_MSG_USERAUTH_PER_METHOD_MAX, NULL);

		/* and try new method */
		if (method->userauth(authctxt) != 0) {
			debug2("we sent a %s packet, wait for reply", method->name);
			break;
		} else {
			debug2("we did not send a packet, disable method");
			method->enabled = NULL;
		}
	}
}