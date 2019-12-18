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
struct bhndb_hw_priority {int /*<<< orphan*/  match; int /*<<< orphan*/ * ports; } ;
struct bhnd_core_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ bhnd_core_matches (struct bhnd_core_info*,int /*<<< orphan*/ *) ; 

const struct bhndb_hw_priority *
bhndb_hw_priority_find_core(const struct bhndb_hw_priority *table,
    struct bhnd_core_info *core)
{
	const struct bhndb_hw_priority	*hp;

	for (hp = table; hp->ports != NULL; hp++) {
		if (bhnd_core_matches(core, &hp->match))
			return (hp);
	}

	/* not found */
	return (NULL);
}