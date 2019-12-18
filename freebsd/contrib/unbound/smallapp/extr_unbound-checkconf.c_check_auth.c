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
struct config_file {int dummy; } ;
struct auth_zones {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_zones_apply_cfg (struct auth_zones*,struct config_file*,int /*<<< orphan*/ ) ; 
 struct auth_zones* auth_zones_create () ; 
 int /*<<< orphan*/  auth_zones_delete (struct auth_zones*) ; 
 int /*<<< orphan*/  fatal_exit (char*) ; 

__attribute__((used)) static void
check_auth(struct config_file* cfg)
{
	struct auth_zones* az = auth_zones_create();
	if(!az || !auth_zones_apply_cfg(az, cfg, 0)) {
		fatal_exit("Could not setup authority zones");
	}
	auth_zones_delete(az);
}