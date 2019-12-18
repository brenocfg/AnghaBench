#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int es_nports; } ;
struct TYPE_5__ {scalar_t__ vlan_mode; } ;
struct cfg {TYPE_2__ info; TYPE_1__ conf; int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {int es_vlangroup; int es_vid; int es_member_ports; int es_untagged_ports; } ;
typedef  TYPE_3__ etherswitch_vlangroup_t ;

/* Variables and functions */
 int ETHERSWITCH_PORTMASK (int) ; 
 int ETHERSWITCH_VID_MASK ; 
 int ETHERSWITCH_VID_VALID ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  IOETHERSWITCHGETVLANGROUP ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_vlangroup(struct cfg *cfg, int vlangroup)
{
	etherswitch_vlangroup_t vg;
	int i, comma;
	
	vg.es_vlangroup = vlangroup;
	if (ioctl(cfg->fd, IOETHERSWITCHGETVLANGROUP, &vg) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHGETVLANGROUP)");
	if ((vg.es_vid & ETHERSWITCH_VID_VALID) == 0)
		return;
	vg.es_vid &= ETHERSWITCH_VID_MASK;
	printf("vlangroup%d:\n", vlangroup);
	if (cfg->conf.vlan_mode == ETHERSWITCH_VLAN_PORT)
		printf("\tport: %d\n", vg.es_vid);
	else
		printf("\tvlan: %d\n", vg.es_vid);
	printf("\tmembers ");
	comma = 0;
	if (vg.es_member_ports != 0)
		for (i=0; i<cfg->info.es_nports; i++) {
			if ((vg.es_member_ports & ETHERSWITCH_PORTMASK(i)) != 0) {
				if (comma)
					printf(",");
				printf("%d", i);
				if ((vg.es_untagged_ports & ETHERSWITCH_PORTMASK(i)) == 0)
					printf("t");
				comma = 1;
			}
		}
	else
		printf("none");
	printf("\n");
}