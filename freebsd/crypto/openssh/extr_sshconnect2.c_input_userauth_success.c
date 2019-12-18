#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct ssh {TYPE_2__* authctxt; } ;
struct TYPE_5__ {int success; int /*<<< orphan*/ * methoddata; TYPE_1__* method; int /*<<< orphan*/ * authlist; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int
input_userauth_success(int type, u_int32_t seq, struct ssh *ssh)
{
	Authctxt *authctxt = ssh->authctxt;

	if (authctxt == NULL)
		fatal("input_userauth_success: no authentication context");
	free(authctxt->authlist);
	authctxt->authlist = NULL;
	if (authctxt->method != NULL && authctxt->method->cleanup != NULL)
		authctxt->method->cleanup(authctxt);
	free(authctxt->methoddata);
	authctxt->methoddata = NULL;
	authctxt->success = 1;			/* break out */
	return 0;
}