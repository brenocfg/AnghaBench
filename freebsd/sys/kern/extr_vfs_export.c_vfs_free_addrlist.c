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
struct ucred {int dummy; } ;
struct TYPE_2__ {struct ucred* netc_anon; } ;
struct netexport {TYPE_1__ ne_defexported; int /*<<< orphan*/ * ne6; int /*<<< orphan*/ * ne4; } ;

/* Variables and functions */
 int /*<<< orphan*/  crfree (struct ucred*) ; 
 int /*<<< orphan*/  vfs_free_addrlist_af (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
vfs_free_addrlist(struct netexport *nep)
{
	struct ucred *cred;

	if (nep->ne4 != NULL)
		vfs_free_addrlist_af(&nep->ne4);
	if (nep->ne6 != NULL)
		vfs_free_addrlist_af(&nep->ne6);

	cred = nep->ne_defexported.netc_anon;
	if (cred != NULL)
		crfree(cred);

}