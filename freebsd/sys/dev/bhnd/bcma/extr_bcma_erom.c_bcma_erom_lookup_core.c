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
struct bhnd_core_match {int dummy; } ;
struct bhnd_core_info {int dummy; } ;
struct bcma_erom {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;

/* Variables and functions */
 int bcma_erom_seek_matching_core (struct bcma_erom*,struct bhnd_core_match const*,struct bhnd_core_info*) ; 

__attribute__((used)) static int
bcma_erom_lookup_core(bhnd_erom_t *erom, const struct bhnd_core_match *desc,
    struct bhnd_core_info *core)
{
	struct bcma_erom *sc = (struct bcma_erom *)erom;

	/* Search for the first matching core */
	return (bcma_erom_seek_matching_core(sc, desc, core));
}