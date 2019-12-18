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
struct portal_group {int dummy; } ;
struct portal {int p_iser; int /*<<< orphan*/  p_listen; int /*<<< orphan*/  p_ai; } ;

/* Variables and functions */
 int /*<<< orphan*/  checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_warnx (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_addr_port (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portal_delete (struct portal*) ; 
 struct portal* portal_new (struct portal_group*) ; 

int
portal_group_add_listen(struct portal_group *pg, const char *value, bool iser)
{
	struct portal *portal;

	portal = portal_new(pg);
	portal->p_listen = checked_strdup(value);
	portal->p_iser = iser;

	if (parse_addr_port(portal->p_listen, "3260", &portal->p_ai)) {
		log_warnx("invalid listen address %s", portal->p_listen);
		portal_delete(portal);
		return (1);
	}

	/*
	 * XXX: getaddrinfo(3) may return multiple addresses; we should turn
	 *	those into multiple portals.
	 */

	return (0);
}