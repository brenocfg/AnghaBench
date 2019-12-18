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
typedef  size_t u_int ;
struct bhndb_port_priority {scalar_t__ type; size_t port; size_t region; } ;
struct bhndb_hw_priority {size_t num_ports; struct bhndb_port_priority* ports; } ;
struct bhnd_core_info {int dummy; } ;
typedef  scalar_t__ bhnd_port_type ;

/* Variables and functions */
 struct bhndb_hw_priority* bhndb_hw_priority_find_core (struct bhndb_hw_priority const*,struct bhnd_core_info*) ; 

const struct bhndb_port_priority *
bhndb_hw_priorty_find_port(const struct bhndb_hw_priority *table,
    struct bhnd_core_info *core, bhnd_port_type port_type, u_int port,
    u_int region)
{
	const struct bhndb_hw_priority		*hp;

	if ((hp = bhndb_hw_priority_find_core(table, core)) == NULL)
		return (NULL);

	for (u_int i = 0; i < hp->num_ports; i++) {
		const struct bhndb_port_priority *pp = &hp->ports[i];

		if (pp->type != port_type)
			continue;

		if (pp->port != port)
			continue;

		if (pp->region != region)
			continue;

		return (pp);
	}

	/* not found */
	return (NULL);
}