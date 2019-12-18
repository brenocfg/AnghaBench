#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cfg {int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {scalar_t__ vlan_mode; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ etherswitch_conf_t ;
typedef  int /*<<< orphan*/  conf ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERSWITCH_CONF_VLAN_MODE ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q_4K ; 
 scalar_t__ ETHERSWITCH_VLAN_DOUBLE_TAG ; 
 scalar_t__ ETHERSWITCH_VLAN_ISL ; 
 scalar_t__ ETHERSWITCH_VLAN_PORT ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  IOETHERSWITCHSETCONF ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static int
set_vlan_mode(struct cfg *cfg, int argc, char *argv[])
{
	etherswitch_conf_t conf;

	if (argc < 2)
		return (-1);

	bzero(&conf, sizeof(conf));
	conf.cmd = ETHERSWITCH_CONF_VLAN_MODE;
	if (strcasecmp(argv[1], "isl") == 0)
		conf.vlan_mode = ETHERSWITCH_VLAN_ISL;
	else if (strcasecmp(argv[1], "port") == 0)
		conf.vlan_mode = ETHERSWITCH_VLAN_PORT;
	else if (strcasecmp(argv[1], "dot1q") == 0)
		conf.vlan_mode = ETHERSWITCH_VLAN_DOT1Q;
	else if (strcasecmp(argv[1], "dot1q4k") == 0)
		conf.vlan_mode = ETHERSWITCH_VLAN_DOT1Q_4K;
	else if (strcasecmp(argv[1], "qinq") == 0)
		conf.vlan_mode = ETHERSWITCH_VLAN_DOUBLE_TAG;
	else
		conf.vlan_mode = 0;
	if (ioctl(cfg->fd, IOETHERSWITCHSETCONF, &conf) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHSETCONF)");

	return (0);
}