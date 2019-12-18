#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ich_arg; int /*<<< orphan*/  ich_func; } ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 char* driver_name_long ; 
 int /*<<< orphan*/  driver_ver ; 
 int /*<<< orphan*/  hpt_final_init ; 
 TYPE_1__ hpt_ich ; 
 int /*<<< orphan*/  init_config () ; 
 int /*<<< orphan*/  os_printk (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  override_kernel_driver () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void hpt_init(void *dummy)
{
	if (bootverbose)
		os_printk("%s %s", driver_name_long, driver_ver);

	override_kernel_driver();
	init_config();

	hpt_ich.ich_func = hpt_final_init;
	hpt_ich.ich_arg = NULL;
	if (config_intrhook_establish(&hpt_ich) != 0) {
		printf("%s: cannot establish configuration hook\n",
		    driver_name_long);
	}

}