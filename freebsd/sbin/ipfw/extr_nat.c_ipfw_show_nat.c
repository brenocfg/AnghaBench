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
struct nat_list_arg {int cmd; int is_all; } ;
struct nat44_cfg_nat {int dummy; } ;
typedef  int /*<<< orphan*/  nla ;
typedef  int /*<<< orphan*/  ipfw_obj_header ;
struct TYPE_2__ {scalar_t__ test_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int IP_FW_NAT44_XGETCONFIG ; 
 int IP_FW_NAT44_XGETLOG ; 
 TYPE_1__ co ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nat_list_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nat_foreach (int /*<<< orphan*/ ,struct nat_list_arg*,int) ; 
 scalar_t__ nat_get_cmd (char*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nat_show_cfg (struct nat44_cfg_nat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nat_show_data ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 

void
ipfw_show_nat(int ac, char **av)
{
	ipfw_obj_header *oh;
	char *name;
	int cmd;
	struct nat_list_arg nla;

	ac--;
	av++;

	if (co.test_only)
		return;

	/* Parse parameters. */
	cmd = 0; /* XXX: Change to IP_FW_NAT44_XGETLOG @ MFC */
	name = NULL;
	for ( ; ac != 0; ac--, av++) {
		if (!strncmp(av[0], "config", strlen(av[0]))) {
			cmd = IP_FW_NAT44_XGETCONFIG;
			continue;
		}
		if (strcmp(av[0], "log") == 0) {
			cmd = IP_FW_NAT44_XGETLOG;
			continue;
		}
		if (name != NULL)
			err(EX_USAGE,"only one instance name may be specified");
		name = av[0];
	}

	if (cmd == 0)
		errx(EX_USAGE, "Please specify action. Available: config,log");

	if (name == NULL) {
		memset(&nla, 0, sizeof(nla));
		nla.cmd = cmd;
		nla.is_all = 1;
		nat_foreach(nat_show_data, &nla, 1);
	} else {
		if (nat_get_cmd(name, cmd, &oh) != 0)
			err(EX_OSERR, "Error getting nat %s instance info", name);
		nat_show_cfg((struct nat44_cfg_nat *)(oh + 1), NULL);
		free(oh);
	}
}