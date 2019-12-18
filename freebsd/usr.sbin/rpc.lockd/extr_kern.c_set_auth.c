#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xucred {int cr_ngroups; int /*<<< orphan*/ * cr_groups; int /*<<< orphan*/  cr_uid; } ;
struct TYPE_8__ {TYPE_1__* ah_ops; } ;
struct TYPE_7__ {TYPE_3__* cl_auth; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ah_destroy ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int NGRPS ; 
 TYPE_3__* authunix_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostname ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void
set_auth(CLIENT *cl, struct xucred *xucred)
{
	int ngroups;

	ngroups = xucred->cr_ngroups - 1;
	if (ngroups > NGRPS)
		ngroups = NGRPS;
        if (cl->cl_auth != NULL)
                cl->cl_auth->ah_ops->ah_destroy(cl->cl_auth);
        cl->cl_auth = authunix_create(hostname,
                        xucred->cr_uid,
                        xucred->cr_groups[0],
                        ngroups,
                        &xucred->cr_groups[1]);
}