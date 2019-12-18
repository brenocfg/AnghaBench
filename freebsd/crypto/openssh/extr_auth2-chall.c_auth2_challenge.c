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
struct ssh {TYPE_1__* authctxt; } ;
struct TYPE_2__ {char* user; int /*<<< orphan*/ * kbdintctxt; } ;
typedef  TYPE_1__ Authctxt ;

/* Variables and functions */
 int auth2_challenge_start (struct ssh*) ; 
 int /*<<< orphan*/  debug (char*,char*,char*) ; 
 int /*<<< orphan*/ * kbdint_alloc (char*) ; 

int
auth2_challenge(struct ssh *ssh, char *devs)
{
	Authctxt *authctxt = ssh->authctxt;
	debug("auth2_challenge: user=%s devs=%s",
	    authctxt->user ? authctxt->user : "<nouser>",
	    devs ? devs : "<no devs>");

	if (authctxt->user == NULL || !devs)
		return 0;
	if (authctxt->kbdintctxt == NULL)
		authctxt->kbdintctxt = kbdint_alloc(devs);
	return auth2_challenge_start(ssh);
}