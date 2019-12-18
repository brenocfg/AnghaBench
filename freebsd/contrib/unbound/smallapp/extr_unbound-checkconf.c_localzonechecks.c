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
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  local_zones_apply_cfg (struct local_zones*,struct config_file*) ; 
 struct local_zones* local_zones_create () ; 
 int /*<<< orphan*/  local_zones_delete (struct local_zones*) ; 

__attribute__((used)) static void
localzonechecks(struct config_file* cfg)
{
	struct local_zones* zs;
	if(!(zs = local_zones_create()))
		fatal_exit("out of memory");
	if(!local_zones_apply_cfg(zs, cfg))
		fatal_exit("failed local-zone, local-data configuration");
	local_zones_delete(zs);
}