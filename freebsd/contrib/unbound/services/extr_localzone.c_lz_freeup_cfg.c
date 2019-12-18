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
struct config_file {int /*<<< orphan*/ * local_data; int /*<<< orphan*/ * local_zones_nodefault; int /*<<< orphan*/ * local_zones; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_deldblstrlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_delstrlist (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lz_freeup_cfg(struct config_file* cfg)
{
	config_deldblstrlist(cfg->local_zones);
	cfg->local_zones = NULL;
	config_delstrlist(cfg->local_zones_nodefault);
	cfg->local_zones_nodefault = NULL;
	config_delstrlist(cfg->local_data);
	cfg->local_data = NULL;
}