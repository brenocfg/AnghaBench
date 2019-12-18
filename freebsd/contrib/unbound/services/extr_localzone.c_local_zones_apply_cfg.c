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
struct local_zones {int dummy; } ;
struct config_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_parents (struct local_zones*) ; 
 int /*<<< orphan*/  local_zone_enter_defaults (struct local_zones*,struct config_file*) ; 
 int /*<<< orphan*/  lz_enter_data (struct local_zones*,struct config_file*) ; 
 int /*<<< orphan*/  lz_enter_overrides (struct local_zones*,struct config_file*) ; 
 int /*<<< orphan*/  lz_enter_zone_tags (struct local_zones*,struct config_file*) ; 
 int /*<<< orphan*/  lz_enter_zones (struct local_zones*,struct config_file*) ; 
 int /*<<< orphan*/  lz_freeup_cfg (struct config_file*) ; 
 int /*<<< orphan*/  lz_setup_implicit (struct local_zones*,struct config_file*) ; 

int 
local_zones_apply_cfg(struct local_zones* zones, struct config_file* cfg)
{
	/* create zones from zone statements. */
	if(!lz_enter_zones(zones, cfg)) {
		return 0;
	}
	/* apply default zones+content (unless disabled, or overridden) */
	if(!local_zone_enter_defaults(zones, cfg)) {
		return 0;
	}
	/* enter local zone overrides */
	if(!lz_enter_overrides(zones, cfg)) {
		return 0;
	}
	/* create implicit transparent zone from data. */
	if(!lz_setup_implicit(zones, cfg)) {
		return 0;
	}

	/* setup parent ptrs for lookup during data entry */
	init_parents(zones);
	/* insert local zone tags */
	if(!lz_enter_zone_tags(zones, cfg)) {
		return 0;
	}
	/* insert local data */
	if(!lz_enter_data(zones, cfg)) {
		return 0;
	}
	/* freeup memory from cfg struct. */
	lz_freeup_cfg(cfg);
	return 1;
}