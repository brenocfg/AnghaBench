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
struct TYPE_3__ {scalar_t__ class; scalar_t__ unit; } ;
struct TYPE_4__ {TYPE_1__ core; } ;
struct bhndb_regwin {scalar_t__ win_type; TYPE_2__ d; } ;
struct bhnd_core_info {scalar_t__ unit; } ;

/* Variables and functions */
 scalar_t__ BHNDB_REGWIN_T_CORE ; 
 scalar_t__ bhnd_core_class (struct bhnd_core_info*) ; 

bool
bhndb_regwin_match_core(const struct bhndb_regwin *regw,
    struct bhnd_core_info *core)
{
	/* Only core windows are supported */
	if (regw->win_type != BHNDB_REGWIN_T_CORE)
		return (false);

	/* Device class must match */
	if (bhnd_core_class(core) != regw->d.core.class)
		return (false);

	/* Device unit must match */
	if (core->unit != regw->d.core.unit)
		return (false);

	/* Matches */
	return (true);
}