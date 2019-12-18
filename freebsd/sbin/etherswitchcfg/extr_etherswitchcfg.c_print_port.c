#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ vlan_mode; } ;
struct cfg {scalar_t__ mediatypes; TYPE_1__ conf; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  p ;
struct TYPE_7__ {int* ifm_ulist; int ifm_count; int ifm_current; scalar_t__ ifm_active; int ifm_status; } ;
struct TYPE_8__ {int es_port; int es_pvid; int es_nleds; size_t* es_led; TYPE_2__ es_ifmr; int /*<<< orphan*/  es_flags; } ;
typedef  TYPE_3__ etherswitch_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERSWITCH_PORT_FLAGS_BITS ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int IFMEDIAREQ_NULISTENTRIES ; 
 int IFM_ACTIVE ; 
 int /*<<< orphan*/  IOETHERSWITCHGETPORT ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 char** ledstyles ; 
 int /*<<< orphan*/  print_media_word (int,int) ; 
 int /*<<< orphan*/  printb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
print_port(struct cfg *cfg, int port)
{
	etherswitch_port_t p;
	int ifm_ulist[IFMEDIAREQ_NULISTENTRIES];
	int i;

	bzero(&p, sizeof(p));
	p.es_port = port;
	p.es_ifmr.ifm_ulist = ifm_ulist;
	p.es_ifmr.ifm_count = IFMEDIAREQ_NULISTENTRIES;
	if (ioctl(cfg->fd, IOETHERSWITCHGETPORT, &p) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHGETPORT)");
	printf("port%d:\n", port);
	if (cfg->conf.vlan_mode == ETHERSWITCH_VLAN_DOT1Q)
		printf("\tpvid: %d\n", p.es_pvid);
	printb("\tflags", p.es_flags, ETHERSWITCH_PORT_FLAGS_BITS);
	printf("\n");
	if (p.es_nleds) {
		printf("\tled: ");
		for (i = 0; i < p.es_nleds; i++) {
			printf("%d:%s%s", i+1, ledstyles[p.es_led[i]], (i==p.es_nleds-1)?"":" ");
		}
		printf("\n");
	}
	printf("\tmedia: ");
	print_media_word(p.es_ifmr.ifm_current, 1);
	if (p.es_ifmr.ifm_active != p.es_ifmr.ifm_current) {
		putchar(' ');
		putchar('(');
		print_media_word(p.es_ifmr.ifm_active, 0);
		putchar(')');
	}
	putchar('\n');
	printf("\tstatus: %s\n", (p.es_ifmr.ifm_status & IFM_ACTIVE) != 0 ? "active" : "no carrier");
	if (cfg->mediatypes) {
		printf("\tsupported media:\n");
		if (p.es_ifmr.ifm_count > IFMEDIAREQ_NULISTENTRIES)
			p.es_ifmr.ifm_count = IFMEDIAREQ_NULISTENTRIES;
		for (i=0; i<p.es_ifmr.ifm_count; i++) {
			printf("\t\tmedia ");
			print_media_word(ifm_ulist[i], 0);
			putchar('\n');
		}
	}
}