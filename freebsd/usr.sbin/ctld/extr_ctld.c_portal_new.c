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
struct portal_group {int /*<<< orphan*/  pg_portals; } ;
struct portal {struct portal_group* p_portal_group; int /*<<< orphan*/  p_targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct portal*,int /*<<< orphan*/ ) ; 
 struct portal* calloc (int,int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  p_next ; 

__attribute__((used)) static struct portal *
portal_new(struct portal_group *pg)
{
	struct portal *portal;

	portal = calloc(1, sizeof(*portal));
	if (portal == NULL)
		log_err(1, "calloc");
	TAILQ_INIT(&portal->p_targets);
	portal->p_portal_group = pg;
	TAILQ_INSERT_TAIL(&pg->pg_portals, portal, p_next);
	return (portal);
}