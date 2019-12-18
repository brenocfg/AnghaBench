#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_6__ {scalar_t__ gss_cleanup_creds; scalar_t__ kerberos_ticket_cleanup; scalar_t__ use_pam; } ;
struct TYPE_5__ {int /*<<< orphan*/  pw; scalar_t__ krb5_ctx; int /*<<< orphan*/  authenticated; } ;
typedef  TYPE_1__ Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/ * auth_info_file ; 
 int /*<<< orphan*/  auth_sock_cleanup_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ is_child ; 
 int /*<<< orphan*/  krb5_cleanup_proc (TYPE_1__*) ; 
 scalar_t__ mm_is_monitor () ; 
 TYPE_2__ options ; 
 int /*<<< orphan*/  restore_uid () ; 
 int /*<<< orphan*/  session_destroy_all (struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_pty_cleanup2 ; 
 int /*<<< orphan*/  ssh_gssapi_cleanup_creds () ; 
 int /*<<< orphan*/  sshpam_cleanup () ; 
 int /*<<< orphan*/  sshpam_thread_cleanup () ; 
 int /*<<< orphan*/  temporarily_use_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_privsep ; 

void
do_cleanup(struct ssh *ssh, Authctxt *authctxt)
{
	static int called = 0;

	debug("do_cleanup");

	/* no cleanup if we're in the child for login shell */
	if (is_child)
		return;

	/* avoid double cleanup */
	if (called)
		return;
	called = 1;

	if (authctxt == NULL)
		return;

#ifdef USE_PAM
	if (options.use_pam) {
		sshpam_cleanup();
		sshpam_thread_cleanup();
	}
#endif

	if (!authctxt->authenticated)
		return;

#ifdef KRB5
	if (options.kerberos_ticket_cleanup &&
	    authctxt->krb5_ctx)
		krb5_cleanup_proc(authctxt);
#endif

#ifdef GSSAPI
	if (options.gss_cleanup_creds)
		ssh_gssapi_cleanup_creds();
#endif

	/* remove agent socket */
	auth_sock_cleanup_proc(authctxt->pw);

	/* remove userauth info */
	if (auth_info_file != NULL) {
		temporarily_use_uid(authctxt->pw);
		unlink(auth_info_file);
		restore_uid();
		free(auth_info_file);
		auth_info_file = NULL;
	}

	/*
	 * Cleanup ptys/utmp only if privsep is disabled,
	 * or if running in monitor.
	 */
	if (!use_privsep || mm_is_monitor())
		session_destroy_all(ssh, session_pty_cleanup2);
}