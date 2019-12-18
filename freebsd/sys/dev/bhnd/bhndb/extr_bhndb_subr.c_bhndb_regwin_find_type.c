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
struct bhndb_regwin {scalar_t__ win_type; scalar_t__ win_size; } ;
typedef  scalar_t__ bus_size_t ;
typedef  scalar_t__ bhndb_regwin_type_t ;

/* Variables and functions */
 scalar_t__ BHNDB_REGWIN_T_INVALID ; 

const struct bhndb_regwin *
bhndb_regwin_find_type(const struct bhndb_regwin *table,
    bhndb_regwin_type_t type, bus_size_t min_size)
{
	const struct bhndb_regwin *rw;

	for (rw = table; rw->win_type != BHNDB_REGWIN_T_INVALID; rw++)
	{
		if (rw->win_type == type && rw->win_size >= min_size)
			return (rw);
	}

	return (NULL);
}