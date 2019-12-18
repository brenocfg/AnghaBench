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
struct portal {struct portal* p_listen; int /*<<< orphan*/ * p_ai; TYPE_1__* p_portal_group; } ;
struct TYPE_2__ {int /*<<< orphan*/  pg_portals; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct portal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct portal*) ; 
 int /*<<< orphan*/  freeaddrinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_next ; 

__attribute__((used)) static void
portal_delete(struct portal *portal)
{

	TAILQ_REMOVE(&portal->p_portal_group->pg_portals, portal, p_next);
	if (portal->p_ai != NULL)
		freeaddrinfo(portal->p_ai);
	free(portal->p_listen);
	free(portal);
}