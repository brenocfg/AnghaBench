#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ class; int unit; scalar_t__ port_type; scalar_t__ port; scalar_t__ region; scalar_t__ offset; } ;
struct TYPE_4__ {TYPE_1__ core; } ;
struct bhndb_regwin {scalar_t__ win_type; scalar_t__ win_size; TYPE_2__ d; } ;
typedef  scalar_t__ bus_size_t ;
typedef  scalar_t__ bhnd_port_type ;
typedef  scalar_t__ bhnd_devclass_t ;

/* Variables and functions */
 scalar_t__ BHNDB_REGWIN_T_CORE ; 
 scalar_t__ BHNDB_REGWIN_T_INVALID ; 

const struct bhndb_regwin *
bhndb_regwin_find_core(const struct bhndb_regwin *table, bhnd_devclass_t class,
    int unit, bhnd_port_type port_type, u_int port, u_int region,
    bus_size_t offset, bus_size_t min_size)
{
	const struct bhndb_regwin *rw;

	for (rw = table; rw->win_type != BHNDB_REGWIN_T_INVALID; rw++)
	{
		bus_size_t rw_offset;

		/* Match on core, port, and region attributes */
		if (rw->win_type != BHNDB_REGWIN_T_CORE)
			continue;

		if (rw->d.core.class != class)
			continue;
		
		if (unit != -1 && rw->d.core.unit != unit)
			continue;

		if (rw->d.core.port_type != port_type)
			continue;

		if (rw->d.core.port != port)
			continue;
		
		if (rw->d.core.region != region)
			continue;

		/* Verify that the requested range is mapped within
		 * this register window */
		if (rw->d.core.offset > offset)
			continue;

		rw_offset = offset - rw->d.core.offset;

		if (rw->win_size < rw_offset)
			continue;

		if (rw->win_size - rw_offset < min_size)
			continue;

		return (rw);
	}

	return (NULL);
}