#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* es_name; int es_nports; int es_nvlangroups; int /*<<< orphan*/  es_vlan_caps; } ;
struct cfg {char* controlfile; TYPE_1__ info; scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERSWITCH_VLAN_CAPS_BITS ; 
 int /*<<< orphan*/  print_config (struct cfg*) ; 
 int /*<<< orphan*/  print_port (struct cfg*,int) ; 
 int /*<<< orphan*/  print_vlangroup (struct cfg*,int) ; 
 int /*<<< orphan*/  printb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
print_info(struct cfg *cfg)
{
	const char *c;
	int i;
	
	c = strrchr(cfg->controlfile, '/');
	if (c != NULL)
		c = c + 1;
	else
		c = cfg->controlfile;
	if (cfg->verbose) {
		printf("%s: %s with %d ports and %d VLAN groups\n", c,
		    cfg->info.es_name, cfg->info.es_nports,
		    cfg->info.es_nvlangroups);
		printf("%s: ", c);
		printb("VLAN capabilities",  cfg->info.es_vlan_caps,
		    ETHERSWITCH_VLAN_CAPS_BITS);
		printf("\n");
	}
	print_config(cfg);
	for (i=0; i<cfg->info.es_nports; i++) {
		print_port(cfg, i);
	}
	for (i=0; i<cfg->info.es_nvlangroups; i++) {
		print_vlangroup(cfg, i);
	}
}