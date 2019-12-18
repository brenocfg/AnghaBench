#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ft5406ts_softc {int sc_tick; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/ * touch_buf; int /*<<< orphan*/ * sc_evdev; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_init_hook; } ;
struct TYPE_7__ {scalar_t__ address; } ;
struct TYPE_8__ {TYPE_3__ resp; } ;
struct TYPE_6__ {int val_buf_size; int val_len; int /*<<< orphan*/  tag; } ;
struct TYPE_5__ {int buf_size; int /*<<< orphan*/  code; } ;
struct bcm2835_mbox_tag_touchbuf {TYPE_4__ body; scalar_t__ end_tag; TYPE_2__ tag_hdr; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_POSITION_X ; 
 int /*<<< orphan*/  ABS_MT_POSITION_Y ; 
 int /*<<< orphan*/  ABS_MT_SLOT ; 
 int /*<<< orphan*/  ABS_MT_TRACKING_ID ; 
 int /*<<< orphan*/  BCM2835_MBOX_CODE_REQ ; 
 int /*<<< orphan*/  BCM2835_MBOX_TAG_GET_TOUCHBUF ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int /*<<< orphan*/  EVDEV_FLAG_MT_AUTOREL ; 
 int /*<<< orphan*/  EVDEV_FLAG_MT_STCOMPAT ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_SYN ; 
 size_t FT5406_NUM_POINTS ; 
 int /*<<< orphan*/  FT5406_WINDOW_SIZE ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 int /*<<< orphan*/  MAX_TOUCH_ID ; 
 int /*<<< orphan*/  NO_POINTS ; 
 int /*<<< orphan*/  SCREEN_HEIGHT ; 
 int /*<<< orphan*/  SCREEN_RES_X ; 
 int /*<<< orphan*/  SCREEN_RES_Y ; 
 int /*<<< orphan*/  SCREEN_WIDTH ; 
 int /*<<< orphan*/  VCBUS_TO_PHYS (scalar_t__) ; 
 int bcm2835_mbox_property (struct bcm2835_mbox_tag_touchbuf*,int) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * evdev_alloc () ; 
 int /*<<< orphan*/  evdev_free (int /*<<< orphan*/ *) ; 
 int evdev_register_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evdev_set_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_methods (int /*<<< orphan*/ *,struct ft5406ts_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evdev_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_phys (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_abs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ft5406ts_evdev_methods ; 
 int hz ; 
 int /*<<< orphan*/  memset (struct bcm2835_mbox_tag_touchbuf*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pmap_mapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ft5406ts_init(void *arg)
{
	struct ft5406ts_softc *sc = arg;
	struct bcm2835_mbox_tag_touchbuf msg;
	uint32_t touchbuf;
	int err;

	/* release this hook (continue boot) */
	config_intrhook_disestablish(&sc->sc_init_hook);

	memset(&msg, 0, sizeof(msg));
	msg.hdr.buf_size = sizeof(msg);
	msg.hdr.code = BCM2835_MBOX_CODE_REQ;
	msg.tag_hdr.tag = BCM2835_MBOX_TAG_GET_TOUCHBUF;
	msg.tag_hdr.val_buf_size = sizeof(msg.body);
	msg.tag_hdr.val_len = sizeof(msg.body);
	msg.end_tag = 0;

	/* call mailbox property */
	err = bcm2835_mbox_property(&msg, sizeof(msg));
	if (err) {
		device_printf(sc->sc_dev, "failed to get touchbuf address\n");
		return;
	}

	if (msg.body.resp.address == 0) {
		device_printf(sc->sc_dev, "touchscreen not detected\n");
		return;
	}

	touchbuf = VCBUS_TO_PHYS(msg.body.resp.address);
	sc->touch_buf = (uint8_t*)pmap_mapdev(touchbuf, FT5406_WINDOW_SIZE);

	/* 60Hz */
	sc->sc_tick = hz * 17 / 1000;
	if (sc->sc_tick == 0)
		sc->sc_tick = 1;

	sc->sc_evdev = evdev_alloc();
	evdev_set_name(sc->sc_evdev, device_get_desc(sc->sc_dev));
	evdev_set_phys(sc->sc_evdev, device_get_nameunit(sc->sc_dev));
	evdev_set_id(sc->sc_evdev, BUS_HOST, 0, 0, 0);
	evdev_set_methods(sc->sc_evdev, sc, &ft5406ts_evdev_methods);
	evdev_set_flag(sc->sc_evdev, EVDEV_FLAG_MT_STCOMPAT);
	evdev_set_flag(sc->sc_evdev, EVDEV_FLAG_MT_AUTOREL);
	evdev_support_prop(sc->sc_evdev, INPUT_PROP_DIRECT);
	evdev_support_event(sc->sc_evdev, EV_SYN);
	evdev_support_event(sc->sc_evdev, EV_ABS);

	evdev_support_abs(sc->sc_evdev, ABS_MT_SLOT, 0, 0,
	    MAX_TOUCH_ID, 0, 0, 0);
	evdev_support_abs(sc->sc_evdev, ABS_MT_TRACKING_ID, 0, -1,
	    MAX_TOUCH_ID, 0, 0, 0);
	evdev_support_abs(sc->sc_evdev, ABS_MT_POSITION_X, 0, 0,
	    SCREEN_WIDTH, 0, 0, SCREEN_RES_X);
	evdev_support_abs(sc->sc_evdev, ABS_MT_POSITION_Y, 0, 0,
	    SCREEN_HEIGHT, 0, 0, SCREEN_RES_Y);

	err = evdev_register_mtx(sc->sc_evdev, &sc->sc_mtx);
	if (err) {
		evdev_free(sc->sc_evdev);
		sc->sc_evdev = NULL;	/* Avoid double free */
		return;
	}

	sc->touch_buf[FT5406_NUM_POINTS] = NO_POINTS;
	callout_init_mtx(&sc->sc_callout, &sc->sc_mtx, 0);
}