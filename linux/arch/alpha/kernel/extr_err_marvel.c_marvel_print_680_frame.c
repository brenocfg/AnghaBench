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
struct ev7_pal_environmental_subpacket {char* module_type; int /*<<< orphan*/  condition; int /*<<< orphan*/  unit_id; int /*<<< orphan*/  drawer; int /*<<< orphan*/  cabinet; } ;
struct ev7_lf_subpackets {struct ev7_pal_environmental_subpacket** env; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_TYPE__PAL__ENV__AIRMOVER_FAN ; 
 int /*<<< orphan*/  EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE ; 
 int /*<<< orphan*/  EL_TYPE__PAL__ENV__HOT_PLUG ; 
 int /*<<< orphan*/  EL_TYPE__PAL__ENV__INTRUSION ; 
 int /*<<< orphan*/  EL_TYPE__PAL__ENV__LAN ; 
 int /*<<< orphan*/  EL_TYPE__PAL__ENV__POWER_SUPPLY ; 
 int /*<<< orphan*/  EL_TYPE__PAL__ENV__VOLTAGE ; 
 int /*<<< orphan*/  err_print_prefix ; 
 size_t ev7_lf_env_index (int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
marvel_print_680_frame(struct ev7_lf_subpackets *lf_subpackets)
{
#ifdef CONFIG_VERBOSE_MCHECK
	struct ev7_pal_environmental_subpacket *env;
	struct { int type; char *name; } ev_packets[] = {
		{ EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE,
		  "Ambient Temperature" },
		{ EL_TYPE__PAL__ENV__AIRMOVER_FAN,
		  "AirMover / Fan" },
		{ EL_TYPE__PAL__ENV__VOLTAGE,
		  "Voltage" },
		{ EL_TYPE__PAL__ENV__INTRUSION,
		  "Intrusion" },
		{ EL_TYPE__PAL__ENV__POWER_SUPPLY,
		  "Power Supply" },
		{ EL_TYPE__PAL__ENV__LAN,
		  "LAN" },
		{ EL_TYPE__PAL__ENV__HOT_PLUG,
		  "Hot Plug" },
		{ 0, NULL }
	};
	int i;

	for (i = 0; ev_packets[i].type != 0; i++) {
		env = lf_subpackets->env[ev7_lf_env_index(ev_packets[i].type)];
		if (!env)
			continue;

		printk("%s**%s event (cabinet %d, drawer %d)\n",
		       err_print_prefix,
		       ev_packets[i].name,
		       env->cabinet,
		       env->drawer);
		printk("%s   Module Type: 0x%x - Unit ID 0x%x - "
		       "Condition 0x%x\n",
		       err_print_prefix,
		       env->module_type,
		       env->unit_id,
		       env->condition);
	}
#endif /* CONFIG_VERBOSE_MCHECK */
}