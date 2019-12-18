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
typedef  int /*<<< orphan*/  uint32_t ;
struct ocs_softc {int /*<<< orphan*/  dbg_lock; TYPE_1__* cdev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {struct ocs_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_OPERATOR ; 
 int /*<<< orphan*/  INT32_MAX ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_cdevsw ; 
 int /*<<< orphan*/  ocs_debug_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_sysctl_init (struct ocs_softc*) ; 
 int resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void
ocs_debug_attach(void *os)
{
	struct ocs_softc *ocs = os;
	int error = 0;
	char *resname = NULL;
	int32_t	unit = INT32_MAX;
	uint32_t ocs_debug_mask = 0;

	resname = "debug_mask";
	if (0 == (error = resource_int_value(device_get_name(ocs->dev), device_get_unit(ocs->dev),
				resname, &ocs_debug_mask))) {
		device_printf(ocs->dev, "setting %s to %010x\n", resname, ocs_debug_mask);
		ocs_debug_enable(ocs_debug_mask);
	}

	unit = device_get_unit(ocs->dev);
	ocs->cdev = make_dev(&ocs_cdevsw, unit, UID_ROOT, GID_OPERATOR, 0640,
			"ocs%d", unit);
	if (ocs->cdev) {
		ocs->cdev->si_drv1 = ocs;
	}

	/* initialize sysctl interface */
	ocs_sysctl_init(ocs);
	mtx_init(&ocs->dbg_lock, "ocs_dbg_lock", NULL, MTX_DEF);
}