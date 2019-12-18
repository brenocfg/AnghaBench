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
struct nat_list_arg {int cmd; int /*<<< orphan*/  is_all; } ;
struct nat44_cfg_nat {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ipfw_obj_header ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
#define  IP_FW_NAT44_XGETCONFIG 129 
#define  IP_FW_NAT44_XGETLOG 128 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nat_get_cmd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nat_show_cfg (struct nat44_cfg_nat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nat_show_log (struct nat44_cfg_nat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nat_show_data(struct nat44_cfg_nat *cfg, void *arg)
{
	struct nat_list_arg *nla;
	ipfw_obj_header *oh;

	nla = (struct nat_list_arg *)arg;

	switch (nla->cmd) {
	case IP_FW_NAT44_XGETCONFIG:
		if (nat_get_cmd(cfg->name, nla->cmd, &oh) != 0) {
			warnx("Error getting nat instance %s info", cfg->name);
			break;
		}
		nat_show_cfg((struct nat44_cfg_nat *)(oh + 1), NULL);
		free(oh);
		break;
	case IP_FW_NAT44_XGETLOG:
		if (nat_get_cmd(cfg->name, nla->cmd, &oh) == 0) {
			nat_show_log((struct nat44_cfg_nat *)(oh + 1), NULL);
			free(oh);
			break;
		}
		/* Handle error */
		if (nla->is_all != 0 && errno == ENOENT)
			break;
		warn("Error getting nat instance %s info", cfg->name);
		break;
	}

	return (0);
}