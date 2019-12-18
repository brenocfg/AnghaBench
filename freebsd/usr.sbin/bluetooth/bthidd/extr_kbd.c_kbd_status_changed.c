#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ leds; } ;
typedef  TYPE_2__ vkbd_status_t ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  st ;
typedef  int int32_t ;
struct TYPE_13__ {scalar_t__ report_ID; int /*<<< orphan*/  usage; } ;
typedef  TYPE_3__ hid_item_t ;
typedef  TYPE_4__* hid_device_p ;
typedef  int /*<<< orphan*/  hid_data_t ;
typedef  TYPE_5__* bthid_session_p ;
struct TYPE_15__ {int /*<<< orphan*/  ukbd; TYPE_1__* srv; int /*<<< orphan*/  intr; int /*<<< orphan*/  bdaddr; } ;
struct TYPE_14__ {scalar_t__ keyboard; int /*<<< orphan*/  desc; } ;
struct TYPE_11__ {scalar_t__ uinput; } ;

/* Variables and functions */
 scalar_t__ HID_PAGE (int /*<<< orphan*/ ) ; 
 int HID_USAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ HUP_LEDS ; 
 scalar_t__ LED_CAP ; 
 scalar_t__ LED_NUM ; 
 scalar_t__ LED_SCR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ NO_REPORT_ID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* get_hid_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_end_parse (int /*<<< orphan*/ ) ; 
 scalar_t__ hid_get_item (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int hid_output ; 
 int /*<<< orphan*/  hid_set_data (scalar_t__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  hid_start_parse (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uinput_rep_leds (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,scalar_t__*,int) ; 

int32_t
kbd_status_changed(bthid_session_p s, uint8_t *data, int32_t len)
{
	vkbd_status_t	st;
	uint8_t		found, report_id;
	hid_device_p	hid_device;
	hid_data_t	d;
	hid_item_t	h;
	uint8_t		leds_mask = 0;

	assert(s != NULL);
	assert(len == sizeof(vkbd_status_t));

	memcpy(&st, data, sizeof(st));
	found = 0;
	report_id = NO_REPORT_ID;

	hid_device = get_hid_device(&s->bdaddr);
	assert(hid_device != NULL);

	data[0] = 0xa2; /* DATA output (HID output report) */
	data[1] = 0x00;
	data[2] = 0x00;

	for (d = hid_start_parse(hid_device->desc, 1 << hid_output, -1);
	     hid_get_item(d, &h) > 0; ) {
		if (HID_PAGE(h.usage) == HUP_LEDS) {
			found++;

			if (report_id == NO_REPORT_ID)
				report_id = h.report_ID;
			else if (h.report_ID != report_id)
				syslog(LOG_WARNING, "Output HID report IDs " \
					"for %s do not match: %d vs. %d. " \
					"Please report",
					bt_ntoa(&s->bdaddr, NULL),
					h.report_ID, report_id);
			
			switch(HID_USAGE(h.usage)) {
			case 0x01: /* Num Lock LED */
				if (st.leds & LED_NUM)
					hid_set_data(&data[1], &h, 1);
				leds_mask |= LED_NUM;
				break;

			case 0x02: /* Caps Lock LED */
				if (st.leds & LED_CAP)
					hid_set_data(&data[1], &h, 1);
				leds_mask |= LED_CAP;
				break;

			case 0x03: /* Scroll Lock LED */
				if (st.leds & LED_SCR)
					hid_set_data(&data[1], &h, 1);
				leds_mask |= LED_SCR;
				break;

			/* XXX add other LEDs ? */
			}
		}
	}
	hid_end_parse(d);

	if (report_id != NO_REPORT_ID) {
		data[2] = data[1];
		data[1] = report_id;
	}

	if (found)
		write(s->intr, data, (report_id != NO_REPORT_ID) ? 3 : 2);

	if (found && s->srv->uinput && hid_device->keyboard)
		uinput_rep_leds(s->ukbd, st.leds, leds_mask);

	return (0);
}