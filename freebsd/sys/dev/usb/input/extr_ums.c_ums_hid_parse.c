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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ums_softc {size_t sc_buttons; struct ums_info* sc_info; } ;
struct TYPE_2__ {int pos; } ;
struct ums_info {int sc_flags; size_t sc_buttons; int /*<<< orphan*/  sc_iid_x; int /*<<< orphan*/ * sc_iid_btn; TYPE_1__* sc_loc_btn; int /*<<< orphan*/  sc_iid_t; TYPE_1__ sc_loc_t; int /*<<< orphan*/  sc_iid_z; TYPE_1__ sc_loc_z; int /*<<< orphan*/  sc_iid_w; TYPE_1__ sc_loc_w; int /*<<< orphan*/  sc_iid_y; TYPE_1__ sc_loc_y; TYPE_1__ sc_loc_x; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HID_USAGE2 (int /*<<< orphan*/ ,size_t) ; 
 size_t HUC_AC_PAN ; 
 size_t HUG_TWHEEL ; 
 size_t HUG_WHEEL ; 
 size_t HUG_X ; 
 size_t HUG_Y ; 
 size_t HUG_Z ; 
 int /*<<< orphan*/  HUP_BUTTON ; 
 int /*<<< orphan*/  HUP_CONSUMER ; 
 int /*<<< orphan*/  HUP_GENERIC_DESKTOP ; 
 int /*<<< orphan*/  HUP_MICROSOFT ; 
 int MOUSE_FLAGS ; 
 int MOUSE_FLAGS_MASK ; 
 size_t UMS_BUTTON_MAX ; 
 int UMS_FLAG_T_AXIS ; 
 int UMS_FLAG_W_AXIS ; 
 int UMS_FLAG_X_AXIS ; 
 int UMS_FLAG_Y_AXIS ; 
 int UMS_FLAG_Z_AXIS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t,char*,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_input ; 
 scalar_t__ hid_locate (size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,TYPE_1__*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ums_hid_parse(struct ums_softc *sc, device_t dev, const uint8_t *buf,
    uint16_t len, uint8_t index)
{
	struct ums_info *info = &sc->sc_info[index];
	uint32_t flags;
	uint8_t i;
	uint8_t j;

	if (hid_locate(buf, len, HID_USAGE2(HUP_GENERIC_DESKTOP, HUG_X),
	    hid_input, index, &info->sc_loc_x, &flags, &info->sc_iid_x)) {

		if ((flags & MOUSE_FLAGS_MASK) == MOUSE_FLAGS) {
			info->sc_flags |= UMS_FLAG_X_AXIS;
		}
	}
	if (hid_locate(buf, len, HID_USAGE2(HUP_GENERIC_DESKTOP, HUG_Y),
	    hid_input, index, &info->sc_loc_y, &flags, &info->sc_iid_y)) {

		if ((flags & MOUSE_FLAGS_MASK) == MOUSE_FLAGS) {
			info->sc_flags |= UMS_FLAG_Y_AXIS;
		}
	}
	/* Try the wheel first as the Z activator since it's tradition. */
	if (hid_locate(buf, len, HID_USAGE2(HUP_GENERIC_DESKTOP,
	    HUG_WHEEL), hid_input, index, &info->sc_loc_z, &flags,
	    &info->sc_iid_z) ||
	    hid_locate(buf, len, HID_USAGE2(HUP_GENERIC_DESKTOP,
	    HUG_TWHEEL), hid_input, index, &info->sc_loc_z, &flags,
	    &info->sc_iid_z)) {
		if ((flags & MOUSE_FLAGS_MASK) == MOUSE_FLAGS) {
			info->sc_flags |= UMS_FLAG_Z_AXIS;
		}
		/*
		 * We might have both a wheel and Z direction, if so put
		 * put the Z on the W coordinate.
		 */
		if (hid_locate(buf, len, HID_USAGE2(HUP_GENERIC_DESKTOP,
		    HUG_Z), hid_input, index, &info->sc_loc_w, &flags,
		    &info->sc_iid_w)) {

			if ((flags & MOUSE_FLAGS_MASK) == MOUSE_FLAGS) {
				info->sc_flags |= UMS_FLAG_W_AXIS;
			}
		}
	} else if (hid_locate(buf, len, HID_USAGE2(HUP_GENERIC_DESKTOP,
	    HUG_Z), hid_input, index, &info->sc_loc_z, &flags, 
	    &info->sc_iid_z)) {

		if ((flags & MOUSE_FLAGS_MASK) == MOUSE_FLAGS) {
			info->sc_flags |= UMS_FLAG_Z_AXIS;
		}
	}
	/*
	 * The Microsoft Wireless Intellimouse 2.0 reports it's wheel
	 * using 0x0048, which is HUG_TWHEEL, and seems to expect you
	 * to know that the byte after the wheel is the tilt axis.
	 * There are no other HID axis descriptors other than X,Y and
	 * TWHEEL
	 */
	if (hid_locate(buf, len, HID_USAGE2(HUP_GENERIC_DESKTOP,
	    HUG_TWHEEL), hid_input, index, &info->sc_loc_t, 
	    &flags, &info->sc_iid_t)) {

		info->sc_loc_t.pos += 8;

		if ((flags & MOUSE_FLAGS_MASK) == MOUSE_FLAGS) {
			info->sc_flags |= UMS_FLAG_T_AXIS;
		}
	} else if (hid_locate(buf, len, HID_USAGE2(HUP_CONSUMER,
		HUC_AC_PAN), hid_input, index, &info->sc_loc_t,
		&flags, &info->sc_iid_t)) {

		if ((flags & MOUSE_FLAGS_MASK) == MOUSE_FLAGS)
			info->sc_flags |= UMS_FLAG_T_AXIS;
	}
	/* figure out the number of buttons */

	for (i = 0; i < UMS_BUTTON_MAX; i++) {
		if (!hid_locate(buf, len, HID_USAGE2(HUP_BUTTON, (i + 1)),
		    hid_input, index, &info->sc_loc_btn[i], NULL, 
		    &info->sc_iid_btn[i])) {
			break;
		}
	}

	/* detect other buttons */

	for (j = 0; (i < UMS_BUTTON_MAX) && (j < 2); i++, j++) {
		if (!hid_locate(buf, len, HID_USAGE2(HUP_MICROSOFT, (j + 1)),
		    hid_input, index, &info->sc_loc_btn[i], NULL, 
		    &info->sc_iid_btn[i])) {
			break;
		}
	}

	info->sc_buttons = i;

	if (i > sc->sc_buttons)
		sc->sc_buttons = i;

	if (info->sc_flags == 0)
		return;

	/* announce information about the mouse */
	device_printf(dev, "%d buttons and [%s%s%s%s%s] coordinates ID=%u\n",
	    (info->sc_buttons),
	    (info->sc_flags & UMS_FLAG_X_AXIS) ? "X" : "",
	    (info->sc_flags & UMS_FLAG_Y_AXIS) ? "Y" : "",
	    (info->sc_flags & UMS_FLAG_Z_AXIS) ? "Z" : "",
	    (info->sc_flags & UMS_FLAG_T_AXIS) ? "T" : "",
	    (info->sc_flags & UMS_FLAG_W_AXIS) ? "W" : "",
	    info->sc_iid_x);
}