#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ich_arg; int /*<<< orphan*/  ich_func; } ;
struct TYPE_8__ {int rate; int resolution; int accelfactor; int /*<<< orphan*/  packetsize; scalar_t__ level; int /*<<< orphan*/  protocol; } ;
struct TYPE_7__ {int buttons; int hwid; int /*<<< orphan*/  model; int /*<<< orphan*/  type; int /*<<< orphan*/  iftype; } ;
struct TYPE_6__ {int /*<<< orphan*/  si_note; } ;
struct cyapa_softc {int reporting_mode; int cap_resx; int cap_resy; int cap_phyx; int cap_phyy; int cap_buttons; TYPE_4__* devnode; int /*<<< orphan*/  mutex; TYPE_5__ intr_hook; int /*<<< orphan*/  dev; TYPE_3__ mode; TYPE_2__ hw; TYPE_1__ selinfo; } ;
struct cyapa_cap {int max_abs_xy_high; int max_abs_x_low; int max_abs_y_low; int phy_siz_xy_high; int phy_siz_x_low; int phy_siz_y_low; int buttons; int /*<<< orphan*/  prod_idc; int /*<<< orphan*/  prod_idb; int /*<<< orphan*/  prod_ida; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_9__ {struct cyapa_softc* si_drv1; } ;

/* Variables and functions */
 int CYAPA_FNGR_LEFT ; 
 int CYAPA_FNGR_MIDDLE ; 
 int CYAPA_FNGR_RIGHT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MOUSE_IF_PS2 ; 
 int /*<<< orphan*/  MOUSE_MODEL_INTELLI ; 
 int /*<<< orphan*/  MOUSE_MOUSE ; 
 int /*<<< orphan*/  MOUSE_PROTO_PS2 ; 
 int /*<<< orphan*/  MOUSE_PS2_PACKETSIZE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ config_intrhook_establish (TYPE_5__*) ; 
 int /*<<< orphan*/  cyapa_cdevsw ; 
 int /*<<< orphan*/  cyapa_start ; 
 struct cyapa_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char,char,int,int) ; 
 int iicbus_get_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ init_device (int /*<<< orphan*/ ,struct cyapa_cap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cyapa_attach(device_t dev)
{
	struct cyapa_softc *sc;
	struct cyapa_cap cap;
	int unit;
	int addr;

	sc = device_get_softc(dev);
	sc->reporting_mode = 1;

	unit = device_get_unit(dev);
	addr = iicbus_get_addr(dev);

	if (init_device(dev, &cap, 0))
		return (ENXIO);

	mtx_init(&sc->mutex, "cyapa", NULL, MTX_DEF);

	sc->dev = dev;

	knlist_init_mtx(&sc->selinfo.si_note, &sc->mutex);

	sc->cap_resx = ((cap.max_abs_xy_high << 4) & 0x0F00) |
	    cap.max_abs_x_low;
	sc->cap_resy = ((cap.max_abs_xy_high << 8) & 0x0F00) |
	    cap.max_abs_y_low;
	sc->cap_phyx = ((cap.phy_siz_xy_high << 4) & 0x0F00) |
	    cap.phy_siz_x_low;
	sc->cap_phyy = ((cap.phy_siz_xy_high << 8) & 0x0F00) |
	    cap.phy_siz_y_low;
	sc->cap_buttons = cap.buttons;

	device_printf(dev, "%5.5s-%6.6s-%2.2s buttons=%c%c%c res=%dx%d\n",
	    cap.prod_ida, cap.prod_idb, cap.prod_idc,
	    ((cap.buttons & CYAPA_FNGR_LEFT) ? 'L' : '-'),
	    ((cap.buttons & CYAPA_FNGR_MIDDLE) ? 'M' : '-'),
	    ((cap.buttons & CYAPA_FNGR_RIGHT) ? 'R' : '-'),
	    sc->cap_resx, sc->cap_resy);

	sc->hw.buttons = 5;
	sc->hw.iftype = MOUSE_IF_PS2;
	sc->hw.type = MOUSE_MOUSE;
	sc->hw.model = MOUSE_MODEL_INTELLI;
	sc->hw.hwid = addr;

	sc->mode.protocol = MOUSE_PROTO_PS2;
	sc->mode.rate = 100;
	sc->mode.resolution = 4;
	sc->mode.accelfactor = 1;
	sc->mode.level = 0;
	sc->mode.packetsize = MOUSE_PS2_PACKETSIZE;

	sc->intr_hook.ich_func = cyapa_start;
	sc->intr_hook.ich_arg = sc->dev;

	/* Postpone start of the polling thread until sleep is available */
	if (config_intrhook_establish(&sc->intr_hook) != 0) {
		mtx_destroy(&sc->mutex);
		return (ENOMEM);
	}

	sc->devnode = make_dev(&cyapa_cdevsw, unit,
	    UID_ROOT, GID_WHEEL, 0600, "cyapa%d", unit);

	sc->devnode->si_drv1 = sc;

	return (0);
}