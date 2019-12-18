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
typedef  scalar_t__ uint32_t ;
struct target {TYPE_1__** t_luns; } ;
struct port {int /*<<< orphan*/  p_ctl_port; struct target* p_target; } ;
struct ctl_lun_map {int plun; scalar_t__ lun; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {scalar_t__ l_ctl_lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_LUN_MAP ; 
 int MAX_LUNS ; 
 void* UINT32_MAX ; 
 int /*<<< orphan*/  ctl_fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ctl_lun_map*) ; 
 int /*<<< orphan*/  log_warn (char*) ; 

int
kernel_port_update(struct port *port, struct port *oport)
{
	struct ctl_lun_map lm;
	struct target *targ = port->p_target;
	struct target *otarg = oport->p_target;
	int error, i;
	uint32_t olun;

	/* Map configured LUNs and unmap others */
	for (i = 0; i < MAX_LUNS; i++) {
		lm.port = port->p_ctl_port;
		lm.plun = i;
		if (targ->t_luns[i] == NULL)
			lm.lun = UINT32_MAX;
		else
			lm.lun = targ->t_luns[i]->l_ctl_lun;
		if (otarg->t_luns[i] == NULL)
			olun = UINT32_MAX;
		else
			olun = otarg->t_luns[i]->l_ctl_lun;
		if (lm.lun == olun)
			continue;
		error = ioctl(ctl_fd, CTL_LUN_MAP, &lm);
		if (error != 0)
			log_warn("CTL_LUN_MAP ioctl failed");
	}
	return (0);
}