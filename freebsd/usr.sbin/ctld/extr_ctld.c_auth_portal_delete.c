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
struct auth_portal {struct auth_portal* ap_initator_portal; TYPE_1__* ap_auth_group; } ;
struct TYPE_2__ {int /*<<< orphan*/  ag_portals; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct auth_portal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_next ; 
 int /*<<< orphan*/  free (struct auth_portal*) ; 

__attribute__((used)) static void
auth_portal_delete(struct auth_portal *ap)
{
	TAILQ_REMOVE(&ap->ap_auth_group->ag_portals, ap, ap_next);

	free(ap->ap_initator_portal);
	free(ap);
}