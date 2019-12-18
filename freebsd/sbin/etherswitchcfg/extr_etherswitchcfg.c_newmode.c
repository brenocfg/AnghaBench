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
struct cfg {int mode; int /*<<< orphan*/  unit; int /*<<< orphan*/  conf; int /*<<< orphan*/  fd; } ;
typedef  enum cmdmode { ____Placeholder_cmdmode } cmdmode ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  IOETHERSWITCHGETCONF ; 
#define  MODE_ATU 134 
#define  MODE_CONFIG 133 
#define  MODE_NONE 132 
#define  MODE_PHYREG 131 
#define  MODE_PORT 130 
#define  MODE_REGISTER 129 
#define  MODE_VLANGROUP 128 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_config (struct cfg*) ; 
 int /*<<< orphan*/  print_port (struct cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_vlangroup (struct cfg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
newmode(struct cfg *cfg, enum cmdmode mode)
{
	if (mode == cfg->mode)
		return;
	switch (cfg->mode) {
	case MODE_NONE:
		break;
	case MODE_CONFIG:
		/*
		 * Read the updated the configuration (it can be different
		 * from the last time we read it).
		 */
		if (ioctl(cfg->fd, IOETHERSWITCHGETCONF, &cfg->conf) != 0)
			err(EX_OSERR, "ioctl(IOETHERSWITCHGETCONF)");
		print_config(cfg);
		break;
	case MODE_PORT:
		print_port(cfg, cfg->unit);
		break;
	case MODE_VLANGROUP:
		print_vlangroup(cfg, cfg->unit);
		break;
	case MODE_REGISTER:
	case MODE_PHYREG:
	case MODE_ATU:
		break;
	}
	cfg->mode = mode;
}