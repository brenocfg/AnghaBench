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
typedef  int /*<<< orphan*/  vg ;
struct cfg {int /*<<< orphan*/  fd; int /*<<< orphan*/  unit; } ;
struct TYPE_4__ {int es_vid; int /*<<< orphan*/  es_vlangroup; } ;
typedef  TYPE_1__ etherswitch_vlangroup_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int IEEE802DOT1Q_VID_MAX ; 
 int /*<<< orphan*/  IOETHERSWITCHGETVLANGROUP ; 
 int /*<<< orphan*/  IOETHERSWITCHSETVLANGROUP ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_vlangroup_vid(struct cfg *cfg, int argc, char *argv[])
{
	int v;
	etherswitch_vlangroup_t vg;

	if (argc < 2)
		return (-1);

	memset(&vg, 0, sizeof(vg));
	v = strtol(argv[1], NULL, 0);
	if (v < 0 || v > IEEE802DOT1Q_VID_MAX)
		errx(EX_USAGE, "vlan must be between 0 and %d", IEEE802DOT1Q_VID_MAX);
	vg.es_vlangroup = cfg->unit;
	if (ioctl(cfg->fd, IOETHERSWITCHGETVLANGROUP, &vg) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHGETVLANGROUP)");
	vg.es_vid = v;
	if (ioctl(cfg->fd, IOETHERSWITCHSETVLANGROUP, &vg) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHSETVLANGROUP)");
	return (0);
}