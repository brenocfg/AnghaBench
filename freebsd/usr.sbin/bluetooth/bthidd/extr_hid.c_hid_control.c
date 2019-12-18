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
typedef  int uint8_t ;
typedef  scalar_t__ int32_t ;
typedef  TYPE_1__* bthid_session_p ;
struct TYPE_4__ {int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  assert (int) ; 
 int bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_close (TYPE_1__*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int,...) ; 

int32_t
hid_control(bthid_session_p s, uint8_t *data, int32_t len)
{
	assert(s != NULL);
	assert(data != NULL);
	assert(len > 0);

	switch (data[0] >> 4) {
        case 0: /* Handshake (response to command) */
		if (data[0] & 0xf)
			syslog(LOG_ERR, "Got handshake message with error " \
				"response 0x%x from %s",
				data[0], bt_ntoa(&s->bdaddr, NULL));
		break;

	case 1: /* HID Control */
		switch (data[0] & 0xf) {
		case 0: /* NOP */
			break;

		case 1: /* Hard reset */
		case 2: /* Soft reset */
			syslog(LOG_WARNING, "Device %s requested %s reset",
				bt_ntoa(&s->bdaddr, NULL),
				((data[0] & 0xf) == 1)? "hard" : "soft");
			break;

		case 3: /* Suspend */
			syslog(LOG_NOTICE, "Device %s requested Suspend",
				bt_ntoa(&s->bdaddr, NULL));
			break;

		case 4: /* Exit suspend */
			syslog(LOG_NOTICE, "Device %s requested Exit Suspend",
				bt_ntoa(&s->bdaddr, NULL));
			break;

		case 5: /* Virtual cable unplug */
			syslog(LOG_NOTICE, "Device %s unplugged virtual cable",
				bt_ntoa(&s->bdaddr, NULL));
			session_close(s);
			break;

		default:
			syslog(LOG_WARNING, "Device %s sent unknown " \
                                "HID_Control message 0x%x",
				bt_ntoa(&s->bdaddr, NULL), data[0]);
			break;
		}
		break;

	default:
		syslog(LOG_WARNING, "Got unexpected message 0x%x on Control " \
			"channel from %s", data[0], bt_ntoa(&s->bdaddr, NULL));
		break;
	}

	return (0);
}